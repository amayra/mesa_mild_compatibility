/*
 * mesa 3-D graphics library
 *
 * Copyright (C) 1999-2006  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \brief Public interface to the VBO module
 * \author Keith Whitwell
 */


#ifndef _VBO_H
#define _VBO_H

#include <stdbool.h>
#include "main/glheader.h"

#ifdef __cplusplus
extern "C" {
#endif

struct gl_vertex_array;
struct gl_context;
struct gl_transform_feedback_object;

struct _mesa_prim
{
   GLuint mode:8;    /**< GL_POINTS, GL_LINES, GL_QUAD_STRIP, etc */
   GLuint indexed:1;
   GLuint begin:1;
   GLuint end:1;
   GLuint weak:1;
   GLuint no_current_update:1;
   GLuint is_indirect:1;
   GLuint pad:18;

   GLuint start;
   GLuint count;
   GLint basevertex;
   GLuint num_instances;
   GLuint base_instance;
   GLuint draw_id;

   GLsizeiptr indirect_offset;
};

/* Would like to call this a "vbo_index_buffer", but this would be
 * confusing as the indices are not neccessarily yet in a non-null
 * buffer object.
 */
struct _mesa_index_buffer
{
   GLuint count;
   unsigned index_size;
   struct gl_buffer_object *obj;
   const void *ptr;
};



GLboolean
_vbo_CreateContext(struct gl_context *ctx);

void
_vbo_DestroyContext(struct gl_context *ctx);

void
vbo_exec_invalidate_state(struct gl_context *ctx);

void
_vbo_install_exec_vtxfmt(struct gl_context *ctx);

void
vbo_initialize_exec_dispatch(const struct gl_context *ctx,
                             struct _glapi_table *exec);

void
vbo_initialize_save_dispatch(const struct gl_context *ctx,
                             struct _glapi_table *exec);

void
vbo_exec_FlushVertices(struct gl_context *ctx, GLuint flags);

void
vbo_save_SaveFlushVertices(struct gl_context *ctx);

void
vbo_save_NotifyBegin(struct gl_context *ctx, GLenum mode);

void
vbo_save_NewList(struct gl_context *ctx, GLuint list, GLenum mode);

void
vbo_save_EndList(struct gl_context *ctx);

void
vbo_save_BeginCallList(struct gl_context *ctx, struct gl_display_list *list);

void
vbo_save_EndCallList(struct gl_context *ctx);


void
_vbo_draw_indirect(struct gl_context *ctx, GLuint mode,
                        struct gl_buffer_object *indirect_data,
                        GLsizeiptr indirect_offset, unsigned draw_count,
                        unsigned stride,
                        struct gl_buffer_object *indirect_draw_count_buffer,
                        GLsizeiptr indirect_draw_count_offset,
                        const struct _mesa_index_buffer *ib);


void
vbo_delete_minmax_cache(struct gl_buffer_object *bufferObj);

void
vbo_get_minmax_indices(struct gl_context *ctx, const struct _mesa_prim *prim,
                       const struct _mesa_index_buffer *ib,
                       GLuint *min_index, GLuint *max_index, GLuint nr_prims);

void
vbo_use_buffer_objects(struct gl_context *ctx);

void
vbo_always_unmap_buffers(struct gl_context *ctx);

void
vbo_sw_primitive_restart(struct gl_context *ctx,
                         const struct _mesa_prim *prim,
                         GLuint nr_prims,
                         const struct _mesa_index_buffer *ib,
                         struct gl_buffer_object *indirect);


/**
 * Utility that tracks and updates the current array entries.
 */
struct vbo_inputs
{
   /**
    * Array of inputs to be set to the _DrawArrays pointer.
    * The array contains pointers into the _DrawVAO and to the vbo modules
    * current values. The array of pointers is updated incrementally
    * based on the current and vertex_processing_mode values below.
    */
   struct gl_vertex_array inputs[VERT_ATTRIB_MAX];
   /** Those VERT_BIT_'s where the inputs array point to current values. */
   GLbitfield current;
   /** Store which aliasing current values - generics or materials - are set. */
   gl_vertex_processing_mode vertex_processing_mode;
};


/**
 * Initialize inputs.
 */
void
_vbo_init_inputs(struct vbo_inputs *inputs);


/**
 * Update the gl_vertex_array array inside the vbo_inputs structure
 * provided the current _VPMode, the provided vao and
 * the vao's enabled arrays filtered by the filter bitmask.
 */
void
_vbo_update_inputs(struct gl_context *ctx, struct vbo_inputs *inputs);


void GLAPIENTRY
_es_Color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

void GLAPIENTRY
_es_Normal3f(GLfloat x, GLfloat y, GLfloat z);

void GLAPIENTRY
_es_MultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);

void GLAPIENTRY
_es_Materialfv(GLenum face, GLenum pname, const GLfloat *params);

void GLAPIENTRY
_es_Materialf(GLenum face, GLenum pname, GLfloat param);

void GLAPIENTRY
_es_VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void GLAPIENTRY
_es_VertexAttrib1f(GLuint indx, GLfloat x);

void GLAPIENTRY
_es_VertexAttrib1fv(GLuint indx, const GLfloat* values);

void GLAPIENTRY
_es_VertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);

void GLAPIENTRY
_es_VertexAttrib2fv(GLuint indx, const GLfloat* values);

void GLAPIENTRY
_es_VertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);

void GLAPIENTRY
_es_VertexAttrib3fv(GLuint indx, const GLfloat* values);

void GLAPIENTRY
_es_VertexAttrib4fv(GLuint indx, const GLfloat* values);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
