#ifndef VOYAGE_EXPORT_H_
#define VOYAGE_EXPORT_H_

#include <stdio.h>
#ifdef _WIN64
    #include "/raylib/raylib-5.0_win64_mingw-w64/include/raylib.h"
#elif __linux__
    #include <raylib.h>
#else
    #error "Unsupported OS; Supported OS (Windows, GNU/Linux)"
#endif
#include "voyage/column.h"
#include "voyage/button.h"
#include "voyage/elements.h"
#include "voyage/helper.h"
#include "voyage/colors.h"
#include "voyage/image.h"
#include "voyage/label.h"
#include "voyage/row.h"
#include "voyage/md.h"
#include "voyage/quote.h"
#include "voyage/space.h"

#endif // VOYAGE_EXPORT_H_
