/*
 * Kitasuna Renga
 *
 * YMap Header File
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


#ifndef _Y_MAP_H_
#define _Y_MAP_H_

#include "yavltree.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Y Pair
 */
struct YPair {
	void *k;
	USERDATA_DESTROYER k_destroyer;
	void *v;
	USERDATA_DESTROYER v_destroyer;
};

/*
 * Allocates a new Y Pair.
 * Returns pointer to the pair, or NULL if failed.
 */
struct YPair *YPairNew(void);

/*
 * Allocates a new Y Pair with initial values for
 * key and value.
 * Returns pointer to the pair, or NULL if failed.
 */
struct YPair *YPairNewWithData(void *key, USERDATA_DESTROYER key_destroyer,
			       void *value, USERDATA_DESTROYER value_destroyer);

/*
 * Release the given Y Pair.
 */
void YPairDelete(struct YPair *yp);

/*
 * Release the given Y Pair with user data.
 */
void YPairDeleteWithData(struct YPair *yp);

/*
 * Getter and setters.
 */
void YPairSetKeyValue(struct YPair *yp,
		      void *key, USERDATA_DESTROYER key_destroyer,
		      void *value, USERDATA_DESTROYER value_destroyer);
void *YPairGetKey(struct YPair *yp);
USERDATA_DESTROYER YPairGetKeyDestroyer(struct YPair *yp);
void *YPairGetValue(struct YPair *yp);
USERDATA_DESTROYER YPairGetValueDestroyer(struct YPair *yp);

/*
 * Function type which compares Y Pairs.
 */
typedef int (*YPAIR_COMPARER)(struct YPair *a, struct YPair *b);



/*
 * Y Map
 */
struct YMap {
	struct YAVLTree tree;
};

/*
 * Initialize the map.
 */
void YMapInit(struct YMap *map);

/*
 * Initialize the map with key comparer.
 */
void YMapInitWithPairComparer(struct YMap *map, YPAIR_COMPARER cmp);

/*
 * Destroy the map.
 */
void YMapDestroy(struct YMap *map);

/*
 * Allocate a new map.
 * Returns pointer to the map, or NULL if failed.
 */
struct YMap *YMapNew(void);

/*
 * Allocate a new map with key comparer.
 * Returns pointer to the map, or NULL if failed.
 */
struct YMap *YMapNewWithPairComparer(YPAIR_COMPARER cmp);

/*
 * Release the given map.
 */
void YMapDelete(struct YMap *map);

/*
 * Setter and getter for Pair comparer
 */
void YMapSetPairComparer(struct YMap *map, YPAIR_COMPARER cmp);
YPAIR_COMPARER YMapGetPairComparer(struct YMap *map);

/*
 * Insert key-value to map.
 * If the key has been set with value already,
 * old value is returned.
 */
void YMapSetKeyValue(struct YMap *map,
		     void *key, USERDATA_DESTROYER key_destroyer,
		     void *value, USERDATA_DESTROYER value_destroyer);

/*
 * Remove key-value from map
 */
void YMapRemoveKeyValue(struct YMap *map, void *key);

/*
 * Get value from map by key
 */
void *YMapGetKeyValue(struct YMap *map, void *key);

/*
 * Get count of pairs of the map
 */
long YMapGetCount(struct YMap *map);

/*
 * Traversal functions
 */
struct YTreeNode *YMapGetFirst(struct YMap *map);
struct YTreeNode *YMapGetLast(struct YMap *map);
struct YTreeNode *YMapGetPrevious(struct YTreeNode *current);
struct YTreeNode *YMapGetNext(struct YTreeNode *current);


#ifdef __cplusplus
}
#endif

#endif // Y_MAP_H
