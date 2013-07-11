/* 26 Nov 02 - Mike: Fixed return types to avoid warnings with gcc */

#include "BinaryFileStub.h"

// text segment of hello pentium
static char pent_hello_text[] = {
    0x6a, 0x00, 0x6a, 0x00, 0x8b, 0xec, 0x52, 0xb8, 0x80, 0x87, 0x04, 0x08, 0x85, 0xc0, 0x74, 0x0d,
    0x68, 0x80, 0x87, 0x04, 0x08, 0xe8, 0x66, 0xff, 0xff, 0xff, 0x83, 0xc4, 0x04, 0xb8, 0x44, 0xa4,
    0x04, 0x08, 0x85, 0xc0, 0x74, 0x05, 0xe8, 0x55, 0xff, 0xff, 0xff, 0x68, 0xe0, 0x93, 0x04, 0x08,
    0xe8, 0x4b, 0xff, 0xff, 0xff, 0x8b, 0x45, 0x08, 0x8d, 0x54, 0x85, 0x10, 0x89, 0x15, 0x0c, 0xaa,
    0x04, 0x08, 0x52, 0x8d, 0x55, 0x0c, 0x52, 0x50, 0xe8, 0x53, 0x0b, 0x00, 0x00, 0xe8, 0x3e, 0xff,
    0xff, 0xff, 0xe8, 0xb1, 0x00, 0x00, 0x00, 0x83, 0xc4, 0x0c, 0x50, 0xe8, 0x40, 0xff, 0xff, 0xff,
    0x6a, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x00, 0x9a, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0xf4, 0xc3,
    0x55, 0x8b, 0xec, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81, 0xc3, 0x8b, 0x1b, 0x00, 0x00,
    0xeb, 0x0f, 0x90, 0x90, 0x8d, 0x50, 0x04, 0x89, 0x93, 0xc8, 0x00, 0x00, 0x00, 0x8b, 0x00, 0xff,
    0xd0, 0x8b, 0x83, 0xc8, 0x00, 0x00, 0x00, 0x83, 0x38, 0x00, 0x75, 0xe8, 0x8d, 0x83, 0xdc, 0x00,
    0x00, 0x00, 0x50, 0xe8, 0xe8, 0x08, 0x00, 0x00, 0x8b, 0x5d, 0xfc, 0xc9, 0xc3, 0x90, 0x90, 0x90,
    0x55, 0x8b, 0xec, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81, 0xc3, 0x4b, 0x1b, 0x00, 0x00,
    0x8b, 0x5d, 0xfc, 0xc9, 0xc3, 0x90, 0x90, 0x90, 0x55, 0x8b, 0xec, 0x53, 0xe8, 0x00, 0x00, 0x00,
    0x00, 0x5b, 0x81, 0xc3, 0x33, 0x1b, 0x00, 0x00, 0x8d, 0x83, 0xdc, 0x05, 0x00, 0x00, 0x50, 0x8d,
    0x83, 0xdc, 0x00, 0x00, 0x00, 0x50, 0xe8, 0x19, 0x08, 0x00, 0x00, 0x8b, 0x5d, 0xfc, 0xc9, 0xc3,
    0x55, 0x8b, 0xec, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81, 0xc3, 0x0b, 0x1b, 0x00, 0x00,
    0x8b, 0x5d, 0xfc, 0xc9, 0xc3, 0x00, 0x00, 0x00, 0x55, 0x8b, 0xec, 0x68, 0xf8, 0x93, 0x04, 0x08,
    0xe8, 0x9b, 0xfe, 0xff, 0xff, 0x83, 0xc4, 0x04, 0x33, 0xc0, 0xeb, 0x00, 0xc9, 0xc3, 0x00, 0x00,
    0x55, 0x8b, 0xec, 0x57, 0x56, 0x33, 0xff, 0x8b, 0xf7, 0x90, 0x90, 0x90, 0x8b, 0x4d, 0x08, 0x0f,
    0xb6, 0x11, 0x41, 0x89, 0x4d, 0x08, 0x8b, 0xc2, 0x25, 0x7f, 0x00, 0x00, 0x00, 0x8b, 0xce, 0xd3,
    0xe0, 0x0b, 0xf8, 0x84, 0xd2, 0x7d, 0x05, 0x83, 0xc6, 0x07, 0xeb, 0xe0, 0x8b, 0x45, 0x0c, 0x89,
    0x38, 0x8b, 0x45, 0x08, 0x8d, 0x65, 0xf8, 0x5e, 0x5f, 0xc9, 0xc3, 0x90, 0x55, 0x8b, 0xec, 0x83,
    0xec, 0x04, 0x57, 0x56, 0x8b, 0x7d, 0x08, 0xc7, 0x45, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x8b, 0x4d,
    0xfc, 0x90, 0x90, 0x90, 0x0f, 0xb6, 0x37, 0x47, 0x8b, 0xc6, 0x25, 0x7f, 0x00, 0x00, 0x00, 0xd3,
    0xe0, 0x09, 0x45, 0xfc, 0x83, 0xc1, 0x07, 0x8b, 0xd6, 0x84, 0xd2, 0x7c, 0xe7, 0x83, 0xf9, 0x1f,
    0x77, 0x12, 0xf7, 0xc6, 0x40, 0x00, 0x00, 0x00, 0x74, 0x0a, 0xb8, 0xff, 0xff, 0xff, 0xff, 0xd3,
    0xe0, 0x09, 0x45, 0xfc, 0x8b, 0x45, 0x0c, 0x8b, 0x55, 0xfc, 0x89, 0x10, 0x8b, 0xc7, 0x8d, 0x65,
    0xf4, 0x5e, 0x5f, 0xc9, 0xc3, 0x90, 0x90, 0x90, 0x55, 0x8b, 0xec, 0x83, 0xec, 0x08, 0x57, 0x56,
    0x8b, 0x55, 0x0c, 0x8b, 0x45, 0x10, 0x8b, 0x75, 0x08, 0x89, 0x04, 0x96, 0x85, 0xd2, 0x74, 0x36,
    0x8d, 0x0c, 0x96, 0x90, 0x8b, 0x39, 0x89, 0x7d, 0xfc, 0x8b, 0x75, 0x08, 0x8b, 0x74, 0x96, 0xfc,
    0x89, 0x75, 0xf8, 0x8b, 0x46, 0x08, 0x8b, 0x77, 0x08, 0x2b, 0xf0, 0x8b, 0xc6, 0x85, 0xc0, 0x7d,
    0x15, 0x8b, 0x7d, 0xf8, 0x89, 0x39, 0x8b, 0x7d, 0xfc, 0x8b, 0x75, 0x08, 0x89, 0x7c, 0x96, 0xfc,
    0x83, 0xc1, 0xfc, 0x4a, 0x75, 0xce, 0x8d, 0x65, 0xf0, 0x5e, 0x5f, 0xc9, 0xc3, 0x90, 0x90, 0x90,
    0x55, 0x8b, 0xec, 0x8b, 0x55, 0x08, 0x33, 0xc9, 0x83, 0x3a, 0x00, 0x74, 0x1d, 0x90, 0x90, 0x90,
    0x83, 0x7a, 0x04, 0x00, 0x74, 0x07, 0x83, 0x7a, 0x08, 0x00, 0x74, 0x01, 0x41, 0x8b, 0xc2, 0x03,
    0x02, 0x8d, 0x50, 0x04, 0x83, 0x78, 0x04, 0x00, 0x75, 0xe6, 0x8b, 0xc1, 0xc9, 0xc3, 0x90, 0x90,
    0x55, 0x8b, 0xec, 0x83, 0xec, 0x08, 0x57, 0x56, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81,
    0xc3, 0xb6, 0x19, 0x00, 0x00, 0x8b, 0x75, 0x08, 0x8b, 0x55, 0x10, 0x8b, 0x3a, 0x8b, 0x4d, 0x14,
    0x8b, 0x09, 0x89, 0x4d, 0xfc, 0x8b, 0x55, 0x18, 0x8b, 0x12, 0x89, 0x55, 0xf8, 0x83, 0x3e, 0x00,
    0x74, 0x3f, 0x90, 0x90, 0x83, 0x7e, 0x04, 0x00, 0x74, 0x2a, 0x83, 0x7e, 0x08, 0x00, 0x74, 0x24,
    0x56, 0x57, 0x47, 0xff, 0x75, 0x0c, 0xe8, 0x2d, 0xff, 0xff, 0xff, 0x8b, 0x46, 0x08, 0x83, 0xc4,
    0x0c, 0x39, 0x45, 0xfc, 0x76, 0x03, 0x89, 0x45, 0xfc, 0x03, 0x46, 0x0c, 0x39, 0x45, 0xf8, 0x73,
    0x03, 0x89, 0x45, 0xf8, 0x8b, 0xc6, 0x03, 0x06, 0x8d, 0x70, 0x04, 0x83, 0x78, 0x04, 0x00, 0x75,
    0xc3, 0x8b, 0x4d, 0x10, 0x89, 0x39, 0x8b, 0x4d, 0xfc, 0x8b, 0x55, 0x14, 0x89, 0x0a, 0x8b, 0x4d,
    0xf8, 0x8b, 0x55, 0x18, 0x89, 0x0a, 0x8d, 0x65, 0xec, 0x5b, 0x5e, 0x5f, 0xc9, 0xc3, 0x90, 0x90,
    0x55, 0x8b, 0xec, 0x83, 0xec, 0x10, 0x57, 0x56, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81,
    0xc3, 0x26, 0x19, 0x00, 0x00, 0x8b, 0x55, 0x08, 0x8b, 0x42, 0x0c, 0x85, 0xc0, 0x74, 0x29, 0x8b,
    0xf0, 0xc7, 0x45, 0xf4, 0x00, 0x00, 0x00, 0x00, 0x83, 0x3e, 0x00, 0x74, 0x2c, 0x90, 0x90, 0x90,
    0xff, 0x36, 0xe8, 0x09, 0xff, 0xff, 0xff, 0x01, 0x45, 0xf4, 0x83, 0xc4, 0x04, 0x83, 0xc6, 0x04,
    0x83, 0x3e, 0x00, 0x75, 0xeb, 0xeb, 0x12, 0x90, 0x8b, 0x55, 0x08, 0xff, 0x72, 0x08, 0xe8, 0xed,
    0xfe, 0xff, 0xff, 0x89, 0x45, 0xf4, 0x83, 0xc4, 0x04, 0x8b, 0x45, 0xf4, 0x8b, 0x55, 0x08, 0x89,
    0x42, 0x10, 0xc1, 0xe0, 0x02, 0x50, 0xe8, 0x85, 0xfc, 0xff, 0xff, 0x8b, 0xf8, 0xc7, 0x45, 0xf8,
    0xff, 0xff, 0xff, 0xff, 0x33, 0xc0, 0x89, 0x45, 0xfc, 0x89, 0x45, 0xf4, 0x83, 0xc4, 0x04, 0x8b,
    0x55, 0x08, 0x8b, 0x42, 0x0c, 0x85, 0xc0, 0x74, 0x2f, 0x8b, 0xf0, 0x83, 0x3e, 0x00, 0x74, 0x40,
    0x8d, 0x55, 0xfc, 0x89, 0x55, 0xf0, 0x90, 0x90, 0xff, 0x75, 0xf0, 0x8d, 0x45, 0xf8, 0x50, 0x8d,
    0x45, 0xf4, 0x50, 0x57, 0xff, 0x36, 0xe8, 0xc5, 0xfe, 0xff, 0xff, 0x83, 0xc4, 0x14, 0x83, 0xc6,
    0x04, 0x83, 0x3e, 0x00, 0x75, 0xe2, 0xeb, 0x18, 0x8d, 0x45, 0xfc, 0x50, 0x8d, 0x45, 0xf8, 0x50,
    0x8d, 0x45, 0xf4, 0x50, 0x57, 0x8b, 0x55, 0x08, 0xff, 0x72, 0x08, 0xe8, 0xa0, 0xfe, 0xff, 0xff,
    0x8b, 0x55, 0x08, 0x89, 0x7a, 0x0c, 0x8b, 0x45, 0xf8, 0x89, 0x02, 0x8b, 0x45, 0xfc, 0x89, 0x42,
    0x04, 0x8d, 0x65, 0xe4, 0x5b, 0x5e, 0x5f, 0xc9, 0xc3, 0x90, 0x90, 0x90, 0x55, 0x8b, 0xec, 0x83,
    0xec, 0x08, 0x57, 0x56, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81, 0xc3, 0x3a, 0x18, 0x00,
    0x00, 0x8b, 0xb3, 0xf4, 0x05, 0x00, 0x00, 0x85, 0xf6, 0x74, 0x74, 0x90, 0x83, 0x3e, 0x00, 0x75,
    0x09, 0x56, 0xe8, 0xe9, 0xfe, 0xff, 0xff, 0x83, 0xc4, 0x04, 0x8b, 0x4d, 0x08, 0x39, 0x0e, 0x77,
    0x05, 0x39, 0x4e, 0x04, 0x77, 0x07, 0x8b, 0x76, 0x14, 0x85, 0xf6, 0x75, 0xdf, 0x85, 0xf6, 0x75,
    0x0b, 0xeb, 0x4c, 0x90, 0x8b, 0x45, 0xf8, 0xeb, 0x48, 0x90, 0x90, 0x90, 0x33, 0xff, 0x8b, 0x4e,
    0x10, 0x89, 0x4d, 0xfc, 0x3b, 0xf9, 0x73, 0x37, 0x8b, 0x76, 0x0c, 0x90, 0x8b, 0x4d, 0xfc, 0x8d,
    0x04, 0x39, 0x8b, 0xd0, 0xd1, 0xea, 0x8b, 0x0c, 0x96, 0x89, 0x4d, 0xf8, 0x8b, 0x41, 0x08, 0x39,
    0x45, 0x08, 0x73, 0x08, 0x89, 0x55, 0xfc, 0xeb, 0x11, 0x90, 0x90, 0x90, 0x8b, 0x4du, 0xf8, 0x03,
    0x41, 0x0c, 0x39, 0x45, 0x08, 0x76, 0xbd, 0x8d, 0x7a, 0x01, 0x39, 0x7d, 0xfc, 0x77u, 0xcd, 0x33,
    0xc0, 0x8d, 0x65, 0xec, 0x5b, 0x5e, 0x5f, 0xc9, 0xc3, 0x90, 0x90, 0x90, 0x55, 0x8bu, 0xec, 0x83,
    0xec, 0x18, 0x57, 0x56, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81, 0xc3, 0x9au, 0x17, 0x00,
    0x00, 0x8b, 0x55, 0x08, 0x8b, 0x42, 0x04, 0x05, 0xfc, 0xff, 0xff, 0xff, 0x2b, 0xd0u, 0x8d, 0x72,
    0x09, 0x89, 0x75, 0xf4, 0x8b, 0x7d, 0x0c, 0x89, 0x37, 0x89, 0x75, 0xf8, 0x8d, 0x83u, 0xf9, 0xef,
    0xff, 0xff, 0x89, 0x45, 0xf0, 0xb9, 0x01, 0x00, 0x00, 0x00, 0x8b, 0xf8, 0xfc, 0xa8u, 0x00, 0xf3,
    0xa6, 0x74, 0x25, 0x8b, 0x75, 0xf4, 0x8d, 0xbb, 0xfa, 0xef, 0xff, 0xff, 0xb9, 0x03u, 0x00, 0x00,
    0x00, 0xfc, 0xa8, 0x00, 0xf3, 0xa6, 0x74, 0x10, 0x80, 0x7a, 0x09, 0x7a, 0x74, 0x0au, 0x33, 0xc0,
    0xe9, 0xa6, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x8b, 0x45, 0x0c, 0x8b, 0x00, 0x89u, 0x45, 0xf0,
    0x8b, 0xd0, 0x8b, 0xfa, 0x33, 0xc0, 0xfc, 0xb9, 0xff, 0xff, 0xff, 0xff, 0xf2, 0xaeu, 0xf7, 0xd1,
    0x89, 0x4d, 0xf8, 0x8d, 0x44, 0x0a, 0xff, 0x89, 0x45, 0xf4, 0x8b, 0xd0, 0x42, 0x8bu, 0x75, 0xf0,
    0x89, 0x75, 0xf8, 0x8d, 0xbb, 0xfa, 0xef, 0xff, 0xff, 0x89, 0x7d, 0xf0, 0xb9, 0x03u, 0x00, 0x00,
    0x00, 0xfc, 0xa8, 0x00, 0xf3, 0xa6, 0x75, 0x14, 0x8b, 0x40, 0x01, 0x8b, 0x75, 0x0cu, 0x89, 0x46,
    0x04, 0x8b, 0x55, 0xf4, 0x83, 0xc2, 0x05, 0xeb, 0x0d, 0x90, 0x90, 0x90, 0x8b, 0x7du, 0x0c, 0xc7,
    0x47, 0x04, 0x00, 0x00, 0x00, 0x00, 0x8b, 0x45, 0x0c, 0x05, 0x08, 0x00, 0x00, 0x00u, 0x50, 0x52,
    0xe8, 0xeb, 0xfb, 0xff, 0xff, 0x8b, 0xd0, 0x8b, 0x75, 0x0c, 0x83, 0xc6, 0x0c, 0x56u, 0x52, 0xe8,
    0x18, 0xfc, 0xff, 0xff, 0x8b, 0xd0, 0x0f, 0xb6, 0x02, 0x8b, 0x75, 0x0c, 0x89, 0x46u, 0x10, 0x42,
    0x8b, 0x3e, 0x83, 0xc4, 0x10, 0x80, 0x3f, 0x7a, 0x75, 0x0f, 0x8d, 0x45, 0xfc, 0x50u, 0x52, 0xe8,
    0xbc, 0xfb, 0xff, 0xff, 0x8b, 0xd0, 0x03, 0x55, 0xfc, 0x8b, 0xc2, 0x8d, 0x65, 0xdcu, 0x5b, 0x5e,
    0x5f, 0xc9, 0xc3, 0x90, 0x55, 0x8b, 0xec, 0x83, 0xec, 0x10, 0x57, 0x56, 0x53, 0xe8u, 0x00, 0x00,
    0x00, 0x00, 0x5b, 0x81, 0xc3, 0x82, 0x16, 0x00, 0x00, 0x8b, 0x7d, 0x10, 0x8b, 0x55u, 0x14, 0x8b,
    0x4d, 0x08, 0x0f, 0xb6, 0x01, 0x41, 0x89, 0x4d, 0x08, 0x8b, 0xf0, 0x81, 0xe6, 0x40u, 0x00, 0x00,
    0x00, 0x89, 0x75, 0xf0, 0x74, 0x12, 0x25, 0x3f, 0x00, 0x00, 0x00, 0x0f, 0xaf, 0x47u, 0x08, 0x01,
    0x02, 0xe9, 0x42, 0x03, 0x00, 0x00, 0x90, 0x90, 0x84, 0xc0, 0x7d, 0x44, 0x25, 0x3fu, 0x00, 0x00,
    0x00, 0x89, 0x45, 0xf8, 0x8d, 0x45, 0xfc, 0x50, 0xff, 0x75, 0x08, 0xe8, 0x50, 0xfbu, 0xff, 0xff,
    0x89, 0x45, 0x08, 0x8b, 0x45, 0xfc, 0x0f, 0xaf, 0x47, 0x0c, 0x89, 0x45, 0xfc, 0x8bu, 0x45, 0xf8,
    0x8b, 0x4d, 0x0c, 0xc6, 0x44, 0x08, 0x5c, 0x01, 0x8b, 0x75, 0xf8, 0x8d, 0x14, 0xb5u, 0x00, 0x00,
    0x00, 0x00, 0x8b, 0x45, 0xfc, 0x89, 0x44, 0x0a, 0x10, 0xe9, 0xfa, 0x02, 0x00, 0x00u, 0x90, 0x90,
    0xa8, 0xc0, 0x74, 0x18, 0x25, 0x3f, 0x00, 0x00, 0x00, 0x89, 0x45, 0xf8, 0x8a, 0x4du, 0xf0, 0x8b,
    0x75, 0x0c, 0x88, 0x4c, 0x30, 0x5c, 0xe9, 0xdd, 0x02, 0x00, 0x00, 0x90, 0x3d, 0x2eu, 0x00, 0x00,
    0x00, 0x0f, 0x87, 0xc9, 0x02, 0x00, 0x00, 0x8b, 0xcb, 0x2b, 0x8c, 0x83, 0x30, 0xeau, 0xff, 0xff,
    0xff, 0xe1, 0x90, 0x90, 0x0c, 0x13, 0x00, 0x00, 0x14, 0x15, 0x00, 0x00, 0x00, 0x15u, 0x00, 0x00,
    0xec, 0x14, 0x00, 0x00, 0xd8, 0x14, 0x00, 0x00, 0xc0, 0x14, 0x00, 0x00, 0x74, 0x14u, 0x00, 0x00,
    0x0c, 0x13, 0x00, 0x00, 0x0c, 0x13, 0x00, 0x00, 0x54, 0x14, 0x00, 0x00, 0xa0, 0x13u, 0x00, 0x00,
    0x80, 0x13, 0x00, 0x00, 0x14, 0x14, 0x00, 0x00, 0xe0, 0x13, 0x00, 0x00, 0xc0, 0x13u, 0x00, 0x00,
    0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13u, 0x00, 0x00,
    0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13u, 0x00, 0x00,
    0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13u, 0x00, 0x00,
    0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13u, 0x00, 0x00,
    0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13u, 0x00, 0x00,
    0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13u, 0x00, 0x00,
    0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x14, 0x13u, 0x00, 0x00,
    0x14, 0x13, 0x00, 0x00, 0x14, 0x13, 0x00, 0x00, 0x64, 0x13, 0x00, 0x00, 0x30, 0x13u, 0x00, 0x00,
    0x8b, 0x75, 0x08, 0x8b, 0x06, 0x89, 0x02, 0x83, 0xc6, 0x04, 0x89, 0x75, 0x08, 0xe9u, 0xf6, 0x01,
    0x00, 0x00, 0x90, 0x90, 0x8b, 0x4d, 0x08, 0x0f, 0xb6, 0x01, 0x01, 0x02, 0x41, 0x89u, 0x4d, 0x08,
    0xe9, 0xe3, 0x01, 0x00, 0x00, 0x90, 0x90, 0x90, 0x8b, 0x75, 0x08, 0x0f, 0xb7, 0x06u, 0x01, 0x02,
    0x83, 0xc6, 0x02, 0x89, 0x75, 0x08, 0xe9, 0xcd, 0x01, 0x00, 0x00, 0x90, 0x8b, 0x02u, 0x8b, 0x4d,
    0x08, 0x03, 0x01, 0x89, 0x02, 0x83, 0xc1, 0x04, 0x89, 0x4d, 0x08, 0xe9, 0xb8, 0x01u, 0x00, 0x00,
    0x90, 0x90, 0x90, 0x90, 0x8d, 0x45, 0xf8, 0x50, 0xff, 0x75, 0x08, 0xe8, 0xd0, 0xf9u, 0xff, 0xff,
    0x89, 0x45, 0x08, 0x8d, 0x45, 0xfc, 0x50, 0xff, 0x75, 0x08, 0xe8, 0xc1, 0xf9, 0xffu, 0xff, 0x89,
    0x45, 0x08, 0x8b, 0x45, 0xfc, 0x0f, 0xaf, 0x47, 0x0c, 0x89, 0x45, 0xfc, 0x8b, 0x45u, 0xf8, 0x8b,
    0x75, 0x0c, 0xc6, 0x44, 0x30, 0x5c, 0x01, 0x8b, 0x4d, 0xf8, 0x8d, 0x14, 0x8d, 0x00u, 0x00, 0x00,
    0x00, 0x8b, 0x45, 0xfc, 0x89, 0x44, 0x32, 0x10, 0xe9, 0x6b, 0x01, 0x00, 0x00, 0x90u, 0x90, 0x90,
    0x8d, 0x45, 0xf8, 0x50, 0xff, 0x75, 0x08, 0xe8, 0x84, 0xf9, 0xff, 0xff, 0x89, 0x45u, 0x08, 0x8b,
    0x45, 0xf8, 0x8b, 0x75, 0x0c, 0xc6, 0x44, 0x30, 0x5c, 0x00, 0xe9, 0x49, 0x01, 0x00u, 0x00, 0x90,
    0x8d, 0x45, 0xf8, 0x50, 0xff, 0x75, 0x08, 0xe8, 0x64, 0xf9, 0xff, 0xff, 0x89, 0x45u, 0x08, 0x8d,
    0x45, 0xf4, 0x50, 0xff, 0x75, 0x08, 0xe8, 0x55, 0xf9, 0xff, 0xff, 0x89, 0x45, 0x08u, 0x8b, 0x45,
    0xf8, 0x8b, 0x4d, 0x0c, 0xc6, 0x44, 0x08, 0x5c, 0x02, 0x8b, 0x75, 0xf8, 0x8d, 0x14u, 0xb5, 0x00,
    0x00, 0x00, 0x00, 0x8b, 0x45, 0xf4, 0x89, 0x44, 0x0a, 0x10, 0xe9, 0x09, 0x01, 0x00u, 0x00, 0x90,
    0x8d, 0x45, 0xf8, 0x50, 0xff, 0x75, 0x08, 0xe8, 0x24, 0xf9, 0xff, 0xff, 0x89, 0x45u, 0x08, 0x8d,
    0x45, 0xfc, 0x50, 0xff, 0x75, 0x08, 0xe8, 0x15, 0xf9, 0xff, 0xff, 0x89, 0x45, 0x08u, 0x8b, 0x45,
    0xf8, 0x8b, 0x4d, 0x0c, 0x66, 0x89, 0x41, 0x58, 0x8b, 0x45, 0xfc, 0x89, 0x41, 0x08u, 0xe9, 0xd5,
    0x00, 0x00, 0x00, 0x90, 0x8d, 0x45, 0xf8, 0x50, 0xff, 0x75, 0x08, 0xe8, 0xf0, 0xf8u, 0xff, 0xff,
    0x89, 0x45, 0x08, 0x8b, 0x45, 0xf8, 0x8b, 0x75, 0x0c, 0x66, 0x89, 0x46, 0x58, 0xe9u, 0xb6, 0x00,
    0x00, 0x00, 0x90, 0x90, 0x8d, 0x45, 0xfc, 0x50, 0xff, 0x75, 0x08, 0xe8, 0xd0, 0xf8u, 0xff, 0xff,
    0x89, 0x45, 0x08, 0x8b, 0x45, 0xfc, 0x8b, 0x4d, 0x0c, 0x89, 0x41, 0x08, 0xe9, 0x97u, 0x00, 0x00,
    0x00, 0x90, 0x90, 0x90, 0x6a, 0x74, 0xe8, 0x55, 0xf7, 0xff, 0xff, 0x8b, 0xd0, 0x8bu, 0xfa, 0x8b,
    0x45, 0x0c, 0x8b, 0xf0, 0xfc, 0xb9, 0x1d, 0x00, 0x00, 0x00, 0xf3, 0xa5, 0x8b, 0x4du, 0x0c, 0x89,
    0x51, 0x70, 0xeb, 0x74, 0x8b, 0x75, 0x0c, 0x8b, 0x56, 0x70, 0x8b, 0xfe, 0x8b, 0xc2u, 0x8b, 0xf0,
    0xfc, 0xb9, 0x1d, 0x00, 0x00, 0x00, 0xf3, 0xa5, 0x52, 0xe8, 0x32, 0xf7, 0xff, 0xffu, 0xeb, 0x58,
    0xc7, 0x45, 0xf8, 0x10, 0x00, 0x00, 0x00, 0x90, 0x8b, 0x45, 0xf8, 0x8b, 0x4d, 0x0cu, 0xc6, 0x44,
    0x08, 0x5c, 0x01, 0x8b, 0x45, 0xf8, 0x8d, 0x14, 0x85, 0xc0, 0xff, 0xff, 0xff, 0x89u, 0x54, 0x81,
    0x10, 0x8d, 0x70, 0x01, 0x89, 0x75, 0xf8, 0x8b, 0xc6, 0x3d, 0x1f, 0x00, 0x00, 0x00u, 0x76, 0xd8,
    0xeb, 0x26, 0x90, 0x90, 0x8d, 0x45, 0xfc, 0x50, 0xff, 0x75, 0x08, 0xe8, 0x40, 0xf8u, 0xff, 0xff,
    0x89, 0x45, 0x08, 0x8b, 0x45, 0xfc, 0x8b, 0x4d, 0x0c, 0x89, 0x41, 0x0c, 0xeb, 0x0au, 0x90, 0x90,
    0xe8, 0xeb, 0xf6, 0xff, 0xff, 0x90, 0x90, 0x90, 0x8b, 0x45, 0x08, 0x8d, 0x65, 0xe4u, 0x5b, 0x5e,
    0x5f, 0xc9, 0xc3, 0x90, 0x55, 0x8b, 0xec, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5bu, 0x81, 0xc3,
    0xf7, 0x12, 0x00, 0x00, 0x8b, 0x45, 0x08, 0x8b, 0x55, 0x0c, 0x89, 0x42, 0x08, 0xc7u, 0x42, 0x04,
    0x00, 0x00, 0x00, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x42, 0x0c, 0x00u, 0x00, 0x00,
    0x00, 0xc7, 0x42, 0x10, 0x00, 0x00, 0x00, 0x00, 0x8b, 0x83, 0xf4, 0x05, 0x00, 0x00u, 0x89, 0x42,
    0x14, 0x89, 0x93, 0xf4, 0x05, 0x00, 0x00, 0x8b, 0x5d, 0xfc, 0xc9, 0xc3, 0x55, 0x8bu, 0xec, 0x53,
    0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81, 0xc3, 0xaf, 0x12, 0x00, 0x00, 0x8b, 0x45u, 0x08, 0x8b,
    0x55, 0x0c, 0x89, 0x42, 0x08, 0x89, 0x42, 0x0c, 0xc7, 0x42, 0x04, 0x00, 0x00, 0x00u, 0x00, 0xc7,
    0x02, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x42, 0x10, 0x00, 0x00, 0x00, 0x00, 0x8b, 0x83u, 0xf4, 0x05,
    0x00, 0x00, 0x89, 0x42, 0x14, 0x89, 0x93, 0xf4, 0x05, 0x00, 0x00, 0x8b, 0x5d, 0xfcu, 0xc9, 0xc3,
    0x55, 0x8b, 0xec, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81, 0xc3, 0x6b, 0x12u, 0x00, 0x00,
    0x8b, 0x45, 0x08, 0x8d, 0x8b, 0xf4, 0x05, 0x00, 0x00, 0x83, 0xbb, 0xf4, 0x05, 0x00u, 0x00, 0x00,
    0x74, 0x27, 0x90, 0x90, 0x8b, 0x11, 0x39, 0x42, 0x08, 0x75, 0x15, 0x8b, 0x42, 0x14u, 0x89, 0x01,
    0x83, 0x3a, 0x00, 0x74, 0x1b, 0xff, 0x72, 0x0c, 0xe8, 0x03, 0xf6, 0xff, 0xff, 0xebu, 0x11, 0x90,
    0x8d, 0x4a, 0x14, 0x83, 0x7a, 0x14, 0x00, 0x75, 0xdb, 0xe8, 0x02, 0xf6, 0xff, 0xffu, 0x90, 0x90,
    0x8b, 0x5d, 0xfc, 0xc9, 0xc3, 0x90, 0x90, 0x90, 0x55, 0x8b, 0xec, 0x81, 0xec, 0xa8u, 0x00, 0x00,
    0x00, 0x57, 0x56, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x81, 0xc3, 0x0b, 0x12u, 0x00, 0x00,
    0xff, 0x75, 0x08, 0xe8, 0xb4, 0xf9, 0xff, 0xff, 0x89, 0x85, 0x6c, 0xff, 0xff, 0xffu, 0x83, 0xc4,
    0x04, 0x85, 0xc0, 0x0f, 0x84, 0x2e, 0x01, 0x00, 0x00, 0x8d, 0x4d, 0xec, 0x89, 0x8du, 0x68, 0xff,
    0xff, 0xff, 0x51, 0xff, 0xb5, 0x6c, 0xff, 0xff, 0xff, 0xe8, 0x2e, 0xfa, 0xff, 0xffu, 0x8b, 0xf0,
    0x83, 0xc4, 0x08, 0x85, 0xf6, 0x0f, 0x84, 0x0c, 0x01, 0x00, 0x00, 0x6a, 0x74, 0x6au, 0x00, 0x8d,
    0x8d, 0x78, 0xff, 0xff, 0xff, 0x89, 0x8d, 0x64, 0xff, 0xff, 0xff, 0x51, 0xe8, 0x9fu, 0xf5, 0xff,
    0xff, 0x8b, 0x45, 0xfc, 0x66, 0x89, 0x45, 0xd2, 0x8b, 0x45, 0xf0, 0x89, 0x85, 0x7cu, 0xff, 0xff,
    0xff, 0x83, 0xc4, 0x0c, 0x8b, 0x8d, 0x6c, 0xff, 0xff, 0xff, 0x8b, 0x41, 0x04, 0x05u, 0xfc, 0xff,
    0xff, 0xff, 0x2b, 0xc8, 0x8b, 0xc1, 0x03, 0x00, 0x8d, 0x78, 0x04, 0x3b, 0xf7, 0x73u, 0x36, 0x8b,
    0x8d, 0x68, 0xff, 0xff, 0xff, 0x89, 0x8d, 0x60, 0xff, 0xff, 0xff, 0x8b, 0x8d, 0x64u, 0xff, 0xff,
    0xff, 0x89, 0x8d, 0x5c, 0xff, 0xff, 0xff, 0x90, 0x6a, 0x00, 0xff, 0xb5, 0x60, 0xffu, 0xff, 0xff,
    0xff, 0xb5, 0x5c, 0xff, 0xff, 0xff, 0x56, 0xe8, 0xc8, 0xfa, 0xff, 0xff, 0x8b, 0xf0u, 0x83, 0xc4,
    0x10, 0x3b, 0xf7, 0x72, 0xe3, 0x8b, 0xb5, 0x6c, 0xff, 0xff, 0xff, 0x83, 0xc6, 0x10u, 0x8b, 0x45,
    0xec, 0x80, 0x38, 0x7a, 0x75, 0x18, 0x8d, 0x85, 0x74, 0xff, 0xff, 0xff, 0x50, 0x56u, 0xe8, 0x4d,
    0xf6, 0xff, 0xff, 0x8b, 0xf0, 0x03, 0xb5, 0x74, 0xff, 0xff, 0xff, 0x83, 0xc4, 0x08u, 0x8b, 0x85,
    0x6c, 0xff, 0xff, 0xff, 0x03, 0x00, 0x8d, 0x78, 0x04, 0x8b, 0x8d, 0x6c, 0xff, 0xffu, 0xff, 0x8b,
    0x41, 0x08, 0x89, 0x85, 0x70, 0xff, 0xff, 0xff, 0x3b, 0xf7, 0x73, 0x37, 0x8d, 0x8du, 0x70, 0xff,
    0xff, 0xff, 0x89, 0x8d, 0x58, 0xff, 0xff, 0xff, 0x8b, 0x4d, 0x08, 0x39, 0x8d, 0x70u, 0xff, 0xff,
    0xff, 0x77, 0x20, 0xff, 0xb5, 0x58, 0xff, 0xff, 0xff, 0x8d, 0x45, 0xec, 0x50, 0x8du, 0x85, 0x78,
    0xff, 0xff, 0xff, 0x50, 0x56, 0xe8, 0x4a, 0xfa, 0xff, 0xff, 0x8b, 0xf0, 0x83, 0xc4u, 0x10, 0x3b,
    0xf7, 0x72, 0xd5, 0x8b, 0x7d, 0x0c, 0x8d, 0xb5, 0x78, 0xff, 0xff, 0xff, 0xfc, 0xb9u, 0x1c, 0x00,
    0x00, 0x00, 0xf3, 0xa5, 0x8b, 0x45, 0x0c, 0x8d, 0xa5, 0x4c, 0xff, 0xff, 0xff, 0x5bu, 0x5e, 0x5f,
    0xc9, 0xc3, 0x00, 0x00, 0x55, 0x8b, 0xec, 0x56, 0x53, 0xe8, 0x00, 0x00, 0x00, 0x00u, 0x5b, 0x81,
    0xc3, 0xa6, 0x10, 0x00, 0x00, 0x8d, 0x83, 0xd0, 0x00, 0x00, 0x00, 0x8d, 0x70, 0xfcu, 0x83, 0x78,
    0xfc, 0xff, 0x74, 0x0c, 0x8b, 0x06, 0xff, 0xd0, 0x83, 0xc6, 0xfc, 0x83, 0x3e, 0xffu, 0x75, 0xf4,
    0x8d, 0x65, 0xf8, 0x5b, 0x5e, 0xc9, 0xc3, 0x90, 0x55, 0x8b, 0xec, 0x53, 0xe8, 0x00u, 0x00, 0x00,
    0x00, 0x5b, 0x81, 0xc3, 0x73, 0x10, 0x00, 0x00, 0x8b, 0x5d, 0xfc, 0xc9, 0xc3
};

BinaryFileStub::BinaryFileStub()
{
    m_iNumSections = 1;
    SectionInfo *text = new SectionInfo();
    text->pSectionName = ".text";
    text->uNativeAddr = 0x8048810;
    text->uHostAddr = (ADDRESS)pent_hello_text;
    text->uSectionSize = sizeof(pent_hello_text);
    text->uSectionEntrySize = 0;
    text->uType = 0;
    text->bCode = 1;
    text->bData = 0;
    text->bBss = 0;
    text->bReadOnly = 1;
    m_pSections = text;
    getTextLimits();
}

LOAD_FMT BinaryFileStub::GetFormat() const
{
    return LOADFMT_ELF;
}

MACHINE BinaryFileStub::GetMachine() const
{
    return MACHINE_PENTIUM;
}

bool BinaryFileStub::isLibrary() const
{
    return false;
}

std::list<const char *> BinaryFileStub::getDependencyList()
{
    assert(false);
    return std::list<const char*> ();
}

ADDRESS BinaryFileStub::getImageBase()
{
    return 0;
}

size_t BinaryFileStub::getImageSize()
{
    return 0;
}

ADDRESS BinaryFileStub::GetFirstHeaderAddress()
{
    return 0;
}

ADDRESS* BinaryFileStub::GetImportStubs(int& numImports)
{
    return NULL;
}

bool    BinaryFileStub::DisplayDetails(const char* fileName, FILE* f)
{
    return false;
}

std::list<SectionInfo*>& BinaryFileStub::GetEntryPoints(const char* pEntry)
{
    return * new std::list<SectionInfo*>;
}

ADDRESS BinaryFileStub::GetMainEntryPoint()
{
    return 0x8048918;
}

ADDRESS BinaryFileStub::GetEntryPoint()
{
    return 0;
}

std::map<ADDRESS, const char*>* BinaryFileStub::GetDynamicGlobalMap()
{
    return new std::map<ADDRESS, const char*>;
}

char* BinaryFileStub::GetStrPtr(int idx, int offset)
{
    return NULL;
}

void BinaryFileStub::SetLinkAndInfo(int idx, int link, int info)
{
    assert(false);
}

bool  BinaryFileStub::RealLoad(const char* sName)
{
    return false;
}

bool BinaryFileStub::PostLoad(void* handle)
{
    return false;
}
