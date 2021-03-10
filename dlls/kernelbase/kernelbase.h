/*
 * Kernelbase internal definitions
 *
 * Copyright 2019 Alexandre Julliard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_KERNELBASE_H
#define __WINE_KERNELBASE_H

#include "windef.h"
#include "winbase.h"

struct pseudo_console
{
    HANDLE signal;
    HANDLE reference;
    HANDLE process;
};

extern WCHAR *file_name_AtoW( LPCSTR name, BOOL alloc ) DECLSPEC_HIDDEN;
extern DWORD file_name_WtoA( LPCWSTR src, INT srclen, LPSTR dest, INT destlen ) DECLSPEC_HIDDEN;
extern void init_startup_info( RTL_USER_PROCESS_PARAMETERS *params ) DECLSPEC_HIDDEN;
extern void init_locale(void) DECLSPEC_HIDDEN;
extern void init_console(void) DECLSPEC_HIDDEN;

extern const WCHAR windows_dir[] DECLSPEC_HIDDEN;
extern const WCHAR system_dir[] DECLSPEC_HIDDEN;

static const BOOL is_win64 = (sizeof(void *) > sizeof(int));
extern BOOL is_wow64 DECLSPEC_HIDDEN;
extern HMODULE KERNELBASE_hModule DECLSPEC_HIDDEN;

static inline BOOL set_ntstatus( NTSTATUS status )
{
    if (status) SetLastError( RtlNtStatusToDosError( status ));
    return !status;
}

/* make the kernel32 names available */
#define HeapAlloc(heap, flags, size) RtlAllocateHeap(heap, flags, size)
#define HeapReAlloc(heap, flags, ptr, size) RtlReAllocateHeap(heap, flags, ptr, size)
#define HeapFree(heap, flags, ptr) RtlFreeHeap(heap, flags, ptr)

#define IDS_NONAME 0
#define IDS_ATG    1
#define IDS_AFG    2
#define IDS_DZA    3
#define IDS_AZE    4
#define IDS_ALB    5
#define IDS_ARM    6
#define IDS_AND    7
#define IDS_AGO    8
#define IDS_ASM    9
#define IDS_ARG    10
#define IDS_AUS    11
#define IDS_AUT    12
#define IDS_BHR    13
#define IDS_BRB    14
#define IDS_BWA    15
#define IDS_BMU    16
#define IDS_BEL    17
#define IDS_BHS    18
#define IDS_BGD    19
#define IDS_BLZ    20
#define IDS_BIH    21
#define IDS_BOL    22
#define IDS_MMR    23
#define IDS_BEN    24
#define IDS_BLR    25
#define IDS_SLB    26
#define IDS_BRA    27
#define IDS_BTN    28
#define IDS_BGR    29
#define IDS_BRN    30
#define IDS_BDI    31
#define IDS_CAN    32
#define IDS_KHM    33
#define IDS_TCD    34
#define IDS_LKA    35
#define IDS_COG    36
#define IDS_COD    37
#define IDS_CHN    38
#define IDS_CHL    39
#define IDS_CMR    40
#define IDS_COM    41
#define IDS_COL    42
#define IDS_CRI    43
#define IDS_CAF    44
#define IDS_CUB    45
#define IDS_CPV    46
#define IDS_CYP    47
#define IDS_DNK    48
#define IDS_DJI    49
#define IDS_DMA    50
#define IDS_DOM    51
#define IDS_ECU    52
#define IDS_EGY    53
#define IDS_IRL    54
#define IDS_GNQ    55
#define IDS_EST    56
#define IDS_ERI    57
#define IDS_SLV    58
#define IDS_ETH    59
#define IDS_CZE    60
#define IDS_FIN    61
#define IDS_FJI    62
#define IDS_FSM    63
#define IDS_FRO    64
#define IDS_FRA    65
#define IDS_GMB    66
#define IDS_GAB    67
#define IDS_GEO    68
#define IDS_GHA    69
#define IDS_GIB    70
#define IDS_GRD    71
#define IDS_GRL    72
#define IDS_DEU    73
#define IDS_GRC    74
#define IDS_GTM    75
#define IDS_GIN    76
#define IDS_GUY    77
#define IDS_HTI    78
#define IDS_HKG    79
#define IDS_HND    80
#define IDS_HRV    81
#define IDS_HUN    82
#define IDS_ISL    83
#define IDS_IDN    84
#define IDS_IND    85
#define IDS_IOT    86
#define IDS_IRN    87
#define IDS_ISR    88
#define IDS_ITA    89
#define IDS_CIV    90
#define IDS_IRQ    91
#define IDS_JPN    92
#define IDS_JAM    93
#define IDS_SJM    94
#define IDS_JOR    95
#define IDS_JHA    96
#define IDS_KEN    97
#define IDS_KGZ    98
#define IDS_PRK    99
#define IDS_KIR    100
#define IDS_KOR    101
#define IDS_KWT    102
#define IDS_KAZ    103
#define IDS_LAO    104
#define IDS_LBN    105
#define IDS_LVA    106
#define IDS_LTU    107
#define IDS_LBR    108
#define IDS_SVK    109
#define IDS_LIE    110
#define IDS_LSO    111
#define IDS_LUX    112
#define IDS_LBY    113
#define IDS_MDG    114
#define IDS_MAC    115
#define IDS_MDA    116
#define IDS_MNG    117
#define IDS_MWI    118
#define IDS_MLI    119
#define IDS_MCO    120
#define IDS_MAR    121
#define IDS_MUS    122
#define IDS_MRT    123
#define IDS_MLT    124
#define IDS_OMN    125
#define IDS_MDV    126
#define IDS_MEX    127
#define IDS_MYS    128
#define IDS_MOZ    129
#define IDS_NER    130
#define IDS_VUT    131
#define IDS_NGA    132
#define IDS_NLD    133
#define IDS_NOR    134
#define IDS_NPL    135
#define IDS_NRU    136
#define IDS_SUR    137
#define IDS_NIC    138
#define IDS_NZL    139
#define IDS_PSE    140
#define IDS_PRY    141
#define IDS_PER    142
#define IDS_PAK    143
#define IDS_POL    144
#define IDS_PAN    145
#define IDS_PRT    146
#define IDS_PNG    147
#define IDS_PLW    148
#define IDS_GNB    149
#define IDS_QAT    150
#define IDS_REU    151
#define IDS_MHL    152
#define IDS_ROU    153
#define IDS_PHL    154
#define IDS_PRI    155
#define IDS_RUS    156
#define IDS_RWA    157
#define IDS_SAU    158
#define IDS_SPM    159
#define IDS_KNA    160
#define IDS_SYC    161
#define IDS_ZAF    162
#define IDS_SEN    163
#define IDS_SVN    164
#define IDS_SLE    165
#define IDS_SMR    166
#define IDS_SGP    167
#define IDS_SOM    168
#define IDS_ESP    169
#define IDS_LCA    170
#define IDS_SDN    171
#define IDS_SVB    172
#define IDS_SWE    173
#define IDS_SYR    174
#define IDS_CHE    175
#define IDS_ARE    176
#define IDS_TTO    177
#define IDS_THA    178
#define IDS_TJK    179
#define IDS_TON    180
#define IDS_TGO    181
#define IDS_STP    182
#define IDS_TUN    183
#define IDS_TUR    184
#define IDS_TUV    185
#define IDS_TWN    186
#define IDS_TKM    187
#define IDS_TZA    188
#define IDS_UGA    189
#define IDS_UKR    190
#define IDS_GBR    191
#define IDS_USA    192
#define IDS_BFA    193
#define IDS_URY    194
#define IDS_UZB    195
#define IDS_VCT    196
#define IDS_VEN    197
#define IDS_VNM    198
#define IDS_VIR    199
#define IDS_VAT    200
#define IDS_NAM    201
#define IDS_WKI    202
#define IDS_WSM    203
#define IDS_SWZ    204
#define IDS_YEM    205
#define IDS_ZMB    206
#define IDS_ZWE    207
#define IDS_SCG    208
#define IDS_MNE    209
#define IDS_SRB    210
#define IDS_CUW    211
#define IDS_SSD    212
#define IDS_AIA    213
#define IDS_ATA    214
#define IDS_ABW    215
#define IDS_ANI    216
#define IDS_ACI    217
#define IDS_BKI    218
#define IDS_BVT    219
#define IDS_CYM    220
#define IDS_CHI    221
#define IDS_CXR    222
#define IDS_CPI    223
#define IDS_CCK    224
#define IDS_COK    225
#define IDS_CSI    226
#define IDS_DGG    227
#define IDS_FLK    228
#define IDS_GUF    229
#define IDS_PYF    230
#define IDS_ATF    231
#define IDS_GLP    232
#define IDS_GUM    233
#define IDS_GTB    234
#define IDS_GGY    235
#define IDS_HMD    236
#define IDS_HLI    237
#define IDS_JVI    238
#define IDS_JEY    239
#define IDS_KGR    240
#define IDS_MTQ    241
#define IDS_MYT    242
#define IDS_MSR    243
#define IDS_ANT    244
#define IDS_NCL    245
#define IDS_NIU    246
#define IDS_NFK    247
#define IDS_MNP    248
#define IDS_PMA    249
#define IDS_PCN    250
#define IDS_RTI    251
#define IDS_SPN    252
#define IDS_SGS    253
#define IDS_SHN    254
#define IDS_TNI    255
#define IDS_TKL    256
#define IDS_TDC    257
#define IDS_TCA    258
#define IDS_VGB    259
#define IDS_WLF    260
#define IDS_AFR    261
#define IDS_ASI    262
#define IDS_EUR    263
#define IDS_IMN    264
#define IDS_MKD    265
#define IDS_MAL    266
#define IDS_MIC    267
#define IDS_MDI    268
#define IDS_NOA    269
#define IDS_PLY    270
#define IDS_CNA    271
#define IDS_OCE    272
#define IDS_SXM    273
#define IDS_STA    274
#define IDS_MAF    275
#define IDS_WRD    276
#define IDS_WEA    277
#define IDS_MIA    278
#define IDS_NRA    279
#define IDS_CTA    280
#define IDS_SEA    281
#define IDS_EAS    282
#define IDS_EAF    283
#define IDS_EEU    284
#define IDS_SEU    285
#define IDS_MEA    286
#define IDS_SAS    287
#define IDS_TLS    288
#define IDS_XKS    289
#define IDS_AMS    290
#define IDS_ALA    291
#define IDS_CRB    292
#define IDS_NEU    293
#define IDS_SAF    294
#define IDS_WEU    295
#define IDS_ANZ    296
#define IDS_BLM    297
#define IDS_UMI    298
#define IDS_LAC    299
#define IDS_BES    300

#endif /* __WINE_KERNELBASE_H */
