#!/bin/bash

# スレーブとして起動
redis-server --replicaof $REDIS_MASTER_HOST $REDIS_MASTER_PORT
