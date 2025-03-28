/*
 * Copyright 2009-present MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <mongoc/mongoc-cluster-private.h>
#include <mongoc/mongoc-server-stream-private.h>
#include <mongoc/mongoc-util-private.h>

mongoc_server_stream_t *
mongoc_server_stream_new (const mongoc_topology_description_t *td,
                          mongoc_server_description_t *sd,
                          mongoc_stream_t *stream)
{
   mongoc_server_stream_t *server_stream;

   BSON_ASSERT (sd);
   BSON_ASSERT (stream);

   server_stream = BSON_ALIGNED_ALLOC (mongoc_server_stream_t);
   server_stream->topology_type = td->type;
   bson_copy_to (&td->cluster_time, &server_stream->cluster_time);
   server_stream->sd = sd;         /* becomes owned */
   server_stream->stream = stream; /* merely borrowed */
   server_stream->must_use_primary = false;
   server_stream->retry_attempted = false;

   return server_stream;
}

void
mongoc_server_stream_cleanup (mongoc_server_stream_t *server_stream)
{
   if (server_stream) {
      mongoc_server_description_destroy (server_stream->sd);
      bson_destroy (&server_stream->cluster_time);
      bson_free (server_stream);
   }
}

/*
 *--------------------------------------------------------------------------
 *
 * mongoc_server_stream_max_bson_obj_size --
 *
 *      Return the max bson object size for the given server stream.
 *
 *--------------------------------------------------------------------------
 */

int32_t
mongoc_server_stream_max_bson_obj_size (mongoc_server_stream_t *server_stream)
{
   return COALESCE (server_stream->sd->max_bson_obj_size, MONGOC_DEFAULT_BSON_OBJ_SIZE);
}

/*
 *--------------------------------------------------------------------------
 *
 * mongoc_server_stream_max_msg_size --
 *
 *      Return the max message size for the given server stream.
 *
 *--------------------------------------------------------------------------
 */

int32_t
mongoc_server_stream_max_msg_size (mongoc_server_stream_t *server_stream)
{
   return COALESCE (server_stream->sd->max_msg_size, MONGOC_DEFAULT_MAX_MSG_SIZE);
}

/*
 *--------------------------------------------------------------------------
 *
 * mongoc_server_stream_max_write_batch_size --
 *
 *      Return the max write batch size for the given server stream.
 *
 *--------------------------------------------------------------------------
 */

int32_t
mongoc_server_stream_max_write_batch_size (mongoc_server_stream_t *server_stream)
{
   return COALESCE (server_stream->sd->max_write_batch_size, MONGOC_DEFAULT_WRITE_BATCH_SIZE);
}
