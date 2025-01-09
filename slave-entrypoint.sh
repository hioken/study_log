#!/bin/bash

# Redisマスターのホストとポートを環境変数で受け取る
REDIS_MASTER_HOST=${REDIS_MASTER_HOST:-redis-master}
REDIS_MASTER_PORT=${REDIS_MASTER_PORT:-6379}

# スレーブとして起動
redis-server --replicaof $REDIS_MASTER_HOST $REDIS_MASTER_PORT
