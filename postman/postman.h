#pragma once

#include <stdlib.h>
#include <stdint.h>

int postman_send_message(uint8_t *msg_buff, size_t msg_buff_size);

size_t postman_hello_message(uint8_t *proto_buff, const size_t buff_size);