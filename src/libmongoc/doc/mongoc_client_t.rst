:man_page: mongoc_client_t

mongoc_client_t
===============

A single-threaded MongoDB connection. See `Connection Pooling <connection-pooling_>`_.

Synopsis
--------

.. code-block:: c

  typedef struct _mongoc_client_t mongoc_client_t;

  typedef mongoc_stream_t *(*mongoc_stream_initiator_t) (
     const mongoc_uri_t *uri,
     const mongoc_host_list_t *host,
     void *user_data,
     bson_error_t *error);

``mongoc_client_t`` is an opaque type that provides access to a MongoDB server,
replica set, or sharded cluster. It maintains management of underlying sockets
and routing to individual nodes based on :symbol:`mongoc_read_prefs_t` or :symbol:`mongoc_write_concern_t`.

Streams
-------

The underlying transport for a given client can be customized, wrapped or replaced by any implementation that fulfills :symbol:`mongoc_stream_t`. A custom transport can be set with :symbol:`mongoc_client_set_stream_initiator()`.

Thread Safety
-------------

``mongoc_client_t`` is *NOT* thread-safe and should only be used from one thread at a time. When used in multi-threaded scenarios, it is recommended that you use the thread-safe :symbol:`mongoc_client_pool_t` to retrieve a ``mongoc_client_t`` for your thread.

Fork Safety
-----------
A :symbol:`mongoc_client_t` is only usable in the parent process after a fork. The child process must call :symbol:`mongoc_client_reset`.

Example
-------

.. literalinclude:: ../examples/example-client.c
   :language: c
   :caption: example-client.c

.. only:: html

  Functions
  ---------

  .. toctree::
    :titlesonly:
    :maxdepth: 1

    mongoc_client_bulkwrite_new
    mongoc_client_command_simple
    mongoc_client_command_simple_with_server_id
    mongoc_client_command_with_opts
    mongoc_client_destroy
    mongoc_client_enable_auto_encryption
    mongoc_client_find_databases_with_opts
    mongoc_client_get_collection
    mongoc_client_get_crypt_shared_version
    mongoc_client_get_database
    mongoc_client_get_database_names
    mongoc_client_get_database_names_with_opts
    mongoc_client_get_default_database
    mongoc_client_get_gridfs
    mongoc_client_get_handshake_description
    mongoc_client_get_read_concern
    mongoc_client_get_read_prefs
    mongoc_client_get_server_description
    mongoc_client_get_server_descriptions
    mongoc_client_get_uri
    mongoc_client_get_write_concern
    mongoc_client_new
    mongoc_client_new_from_uri
    mongoc_client_new_from_uri_with_error
    mongoc_client_read_command_with_opts
    mongoc_client_read_write_command_with_opts
    mongoc_client_reset
    mongoc_client_select_server
    mongoc_client_set_apm_callbacks
    mongoc_client_set_appname
    mongoc_client_set_error_api
    mongoc_client_set_read_concern
    mongoc_client_set_read_prefs
    mongoc_client_set_server_api
    mongoc_client_set_sockettimeoutms
    mongoc_client_set_ssl_opts
    mongoc_client_set_stream_initiator
    mongoc_client_set_structured_log_opts
    mongoc_client_set_write_concern
    mongoc_client_start_session
    mongoc_client_watch
    mongoc_client_write_command_with_opts
    mongoc_handshake_data_append
