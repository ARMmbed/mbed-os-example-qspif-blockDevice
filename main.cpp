/* mbed Microcontroller Library
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// QSPI SFDP Flash - Block Device example
#include "mbed.h"
#include "QSPIFBlockDevice.h"

QSPIFBlockDevice blockD(MBED_CONF_QSPIF_QSPI_IO0,MBED_CONF_QSPIF_QSPI_IO1,MBED_CONF_QSPIF_QSPI_IO2,MBED_CONF_QSPIF_QSPI_IO3,
		MBED_CONF_QSPIF_QSPI_CLK,MBED_CONF_QSPIF_QSPI_CS,0,MBED_CONF_QSPIF_QSPI_FREQ);


int main() {
    printf("QSPI SFDP Flash Block Device example\n");

    // Initialize the SPI flash device and print the memory layout
    blockD.init();
    bd_size_t sector_size_at_address_0 = blockD.get_erase_size(0);

    printf("QSPIF BD size: %llu\n",         blockD.size());
    printf("QSPIF BD read size: %llu\n",    blockD.get_read_size());
    printf("QSPIF BD program size: %llu\n", blockD.get_program_size());

    printf("QSPIF BD erase size (at address 0): %llu\n", sector_size_at_address_0);

    // Write "Hello World!" to the first block
    char *buffer = (char*) malloc(sector_size_at_address_0);
    sprintf(buffer, "Hello World!\n");
    blockD.erase(0, sector_size_at_address_0);
    blockD.program(buffer, 0, sector_size_at_address_0);

    // Read back what was stored
    blockD.read(buffer, 0, sector_size_at_address_0);
    printf("%s", buffer);

    // Deinitialize the device
    blockD.deinit();
}
