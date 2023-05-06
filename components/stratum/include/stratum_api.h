#ifndef STRATUM_API_H
#define STRATUM_API_H

#include "cJSON.h"
#include <stdint.h>

#define MAX_MERKLE_BRANCHES 32
#define HASH_SIZE 32
#define COINBASE_SIZE 100
#define COINBASE2_SIZE 128

typedef struct {
    char * job_id;
    char * prev_block_hash;
    char * coinbase_1;
    char * coinbase_2;
    uint8_t * merkle_branches;
    size_t n_merkle_branches;
    uint32_t version;
    uint32_t curtime;
    uint32_t bits;
    uint32_t target;
    uint32_t nonce;
} mining_notify;

typedef enum {
    STRATUM_UNKNOWN,
    MINING_NOTIFY,
    MINING_SET_DIFFICULTY
} stratum_method;

void initialize_stratum_buffer();

char * receive_jsonrpc_line(int sockfd);

int subscribe_to_stratum(int socket, char ** extranonce, int * extranonce2_len);

stratum_method parse_stratum_method(const char * stratum_json);

mining_notify parse_mining_notify_message(const char * stratum_json);

void free_mining_notify(mining_notify params);

int parse_stratum_subscribe_result_message(const char * result_json_str,
                                           char ** extranonce,
                                           int * extranonce2_len);

int auth_to_stratum(int socket, const char * username);

#endif // STRATUM_API_H