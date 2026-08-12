#pragma once

/* define dcu firmware version 06.80.09.XX.XX.XX */
#define PRODUCT_TYPE     "06"
#define VEHICLE_TYPE     "80"
#define MODULE_TYPE      "09"
#define DCU_MAIN_VER     "02"
#define DCU_SUB_VER      "03"
#define DCU_CHANGE_FLAG  "03"

#define DCU_VERSION     PRODUCT_TYPE "."  \
                        VEHICLE_TYPE "."  \
                        MODULE_TYPE "."   \
                        DCU_MAIN_VER "."  \
                        DCU_SUB_VER "."   \
                        DCU_CHANGE_FLAG
// newline
