idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                                 "include"
                    EMBED_TXTFILES "certs/servercert.pem"
                                   "certs/prvtkey.pem")
