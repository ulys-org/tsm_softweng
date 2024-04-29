/**
 * @file lv_snapshot.h
 *
 */

#ifndef LV_SNAPSHOT_H
#define LV_SNAPSHOT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stddef.h>

#include "../../../lv_conf_internal.h"
#include "../../../core/lv_obj.h"

/*********************
 *      DEFINES
 *********************/

#if LV_USE_SNAPSHOT
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/** Take snapshot for object with its children.
 *
 * @param obj    The object to generate snapshot.
 * @param cf     color format for generated image.
 *
 * @return a pointer to an image descriptor, or NULL if failed.
 */
lv_img_dsc_t * lv_snapshot_take(lv_obj_t * obj, lv_img_cf_t cf);

/** Free the snapshot image returned by @ref lv_snapshot_take
 *
 * It will firstly free the data image takes, then the image descriptor.
 *
 * @param dsc    The image descriptor generated by lv_snapshot_take.
 *
 */
void lv_snapshot_free(lv_img_dsc_t * dsc);

/** Get the buffer needed for object snapshot image.
 *
 * @param obj    The object to generate snapshot.
 * @param cf     color format for generated image.
 *
 * @return the buffer size needed in bytes
 */
uint32_t lv_snapshot_buf_size_needed(lv_obj_t * obj, lv_img_cf_t cf);

/** Take snapshot for object with its children, save image info to provided buffer.
 *
 * @param obj    The object to generate snapshot.
 * @param cf     color format for generated image.
 * @param dsc    image descriptor to store the image result.
 * @param buff   the buffer to store image data.
 * @param buff_size provided buffer size in bytes.
 *
 * @return LV_RES_OK on success, LV_RES_INV on error.
 */
lv_res_t lv_snapshot_take_to_buf(lv_obj_t * obj, lv_img_cf_t cf, lv_img_dsc_t * dsc, void * buf, uint32_t buff_size);


/**********************
 *      MACROS
 **********************/
#endif /*LV_USE_SNAPSHOT*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
