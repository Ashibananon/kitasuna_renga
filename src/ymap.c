/*
 * Kitasuna Renga
 *
 * YMap Source File
 *
 * Copyright(C) 2020 Ashibananon(Yuan).
 *
 *
 * This file is part of Kitasuna Renga.
 *
 * Kitasuna Renga is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Kitasuna Renga is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Kitasuna Renga.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


#include <stdlib.h>

#include "ymap.h"


struct YPair *YPairNew(void)
{
	struct YPair *yp = (struct YPair *)malloc(sizeof(struct YPair));
	if (yp != NULL) {
		yp->k = NULL;
		yp->v = NULL;
	}

	return yp;
}


struct YPair *YPairNewWithData(void *key, USERDATA_DESTROYER key_destroyer,
			       void *value, USERDATA_DESTROYER value_destroyer)
{
	struct YPair *yp = (struct YPair *)malloc(sizeof(struct YPair));
	if (yp != NULL) {
		yp->k = key;
		yp->k_destroyer = key_destroyer;
		yp->v = value;
		yp->v_destroyer = value_destroyer;
	}

	return yp;
}


void YPairDelete(struct YPair *yp)
{
	if (yp != NULL)
		free(yp);
}


void YPairDeleteWithData(struct YPair *yp)
{
	if (yp != NULL) {
		if (yp->k_destroyer != NULL) {
			yp->k_destroyer(yp->k);
		}
		if (yp->v_destroyer != NULL) {
			yp->v_destroyer(yp->v);
		}
		free(yp);
	}
}


void YPairSetKeyValue(struct YPair *yp,
		      void *key, USERDATA_DESTROYER key_destroyer,
		      void *value, USERDATA_DESTROYER value_destroyer)
{
	if (yp != NULL) {
		yp->k = key;
		yp->k_destroyer = key_destroyer;
		yp->v = value;
		yp->v_destroyer = value_destroyer;
	}
}


void *YPairGetKey(struct YPair *yp)
{
	void *ret = NULL;
	if (yp != NULL)
		ret = yp->k;

	return ret;
}


USERDATA_DESTROYER YPairGetKeyDestroyer(struct YPair *yp)
{
	USERDATA_DESTROYER ret = NULL;
	if (yp != NULL)
		ret = yp->k_destroyer;

	return ret;
}


void *YPairGetValue(struct YPair *yp)
{
	void *ret = NULL;
	if (yp != NULL)
		ret = yp->v;

	return ret;
}


USERDATA_DESTROYER YPairGetValueDestroyer(struct YPair *yp)
{
	USERDATA_DESTROYER ret = NULL;
	if (yp != NULL)
		ret = yp->v_destroyer;

	return ret;
}


/*
 * YMap
 */

void YMapInit(struct YMap *map)
{
	if (map != NULL) {
		YAVLTreeInit(&map->tree);
	}
}


void YMapInitWithPairComparer(struct YMap *map, YPAIR_COMPARER cmp)
{
	if (map != NULL) {
		YAVLTreeInitWithData(&map->tree, (USERDATA_COMPARER)cmp);
	}
}


void YMapDestroy(struct YMap *map)
{
	if (map != NULL) {
		YAVLTreeDestroy(&map->tree);
	}
}


struct YMap *YMapNew(void)
{
	struct YMap *map = (struct YMap *)malloc(sizeof(struct YMap));
	if (map != NULL) {
		YMapInit(map);
	}

	return map;
}


struct YMap *YMapNewWithPairComparer(YPAIR_COMPARER cmp)
{
	struct YMap *map = (struct YMap *)malloc(sizeof(struct YMap));
	if (map != NULL) {
		YMapInitWithPairComparer(map, cmp);
	}

	return map;
}


void YMapDelete(struct YMap *map)
{
	if (map != NULL) {
		YMapDestroy(map);
		free(map);
	}
}


void YMapSetPairComparer(struct YMap *map, YPAIR_COMPARER cmp)
{
	if (map != NULL) {
		YAVLTreeSetDataComparer(&map->tree, (USERDATA_COMPARER)cmp);
	}
}


YPAIR_COMPARER YMapGetPairComparer(struct YMap *map)
{
	YPAIR_COMPARER ret = NULL;
	if (map != NULL) {
		ret = (YPAIR_COMPARER)YAVLTreeGetDataComparer(&map->tree);
	}

	return ret;
}


void YMapSetKeyValue(struct YMap *map,
		      void *key, USERDATA_DESTROYER key_destroyer,
		      void *value, USERDATA_DESTROYER value_destroyer)
{
	if (map == NULL || key == NULL)
		return;

	struct YPair *pair = YPairNewWithData(key, key_destroyer, value, value_destroyer);

	struct YTreeNode *node = YAVLTreeFind(&map->tree, pair);
	if (node == NULL) {
		YAVLTreeInsert(&map->tree, pair, (USERDATA_DESTROYER)YPairDeleteWithData);
	} else {
		YPairDelete(pair);
		if (key_destroyer != NULL) {
			key_destroyer(key);
		}
		struct YPair *pp = (struct YPair *)YTreeNodeGetData(node);
		if (pp != NULL) {
			if (pp->v != value) {
				if (pp->v_destroyer != NULL) {
					pp->v_destroyer(pp->v);
				}

				pp->v = value;
				pp->v_destroyer = value_destroyer;
			}
		}
	}
}


void YMapRemoveKeyValue(struct YMap *map, void *key)
{
	if (map == NULL || key == NULL)
		return;

	struct YPair pair;
	pair.k = key;
	pair.v = NULL;

	struct YTreeNode *node = YAVLTreeFind(&map->tree, &pair);
	YTreeNodeDeleteWithData(YAVLTreeRemove(&map->tree, node));
}


void *YMapGetKeyValue(struct YMap *map, void *key)
{
	void *ret = NULL;

	if (map == NULL || key == NULL)
		return ret;

	struct YPair pair;
	YPairSetKeyValue(&pair, key, NULL, NULL, NULL);

	struct YTreeNode *node = YAVLTreeFind(&map->tree, &pair);
	struct YPair *yp = (struct YPair *)YTreeNodeGetData(node);
	if (yp != NULL)
		ret = yp->v;

	return ret;
}


long YMapGetCount(struct YMap *map)
{
	long ret = -1;
	if (map != NULL) {
		ret = YAVLTreeGetCount(&map->tree);
	}

	return ret;
}


struct YTreeNode *YMapGetFirst(struct YMap *map)
{
	if (map == NULL)
		return NULL;

	return YAVLTreeGetMinimum(&map->tree);
}


struct YTreeNode *YMapGetLast(struct YMap *map)
{
	if (map == NULL)
		return NULL;

	return YAVLTreeGetMaximum(&map->tree);
}


struct YTreeNode *YMapGetPrevious(struct YTreeNode *current)
{
	return YAVLTreeGetPrevious(current);
}


struct YTreeNode *YMapGetNext(struct YTreeNode *current)
{
	return YAVLTreeGetNext(current);
}
