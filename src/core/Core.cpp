//
// Created by 13021 on 2023/3/13.
//

#include <Core.h>
#include "WordChainCoreInterface.h"
int Core::gen_chain_char(char **words, int len, char **result, char head, char tail, char disallowed_head,
                         bool enable_loop) {
    return core::WordChainCoreInterface::gen_chain_char(words, len, result, head, tail, disallowed_head, enable_loop);
}

int Core::gen_chain_word(char **words, int len, char **result, char head, char tail, char disallowed_head,
                         bool enable_loop) {
    return core::WordChainCoreInterface::gen_chain_word(words, len, result, head, tail, disallowed_head, enable_loop);
}

int Core::gen_chains_all(char **words, int len, char **result) {
    return core::WordChainCoreInterface::gen_chains_all(words, len, result);
}