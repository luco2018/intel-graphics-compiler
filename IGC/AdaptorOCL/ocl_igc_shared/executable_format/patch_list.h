/*===================== begin_copyright_notice ==================================

Copyright (c) 2017 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


======================= end_copyright_notice ==================================*/
/*****************************************************************************\
Abstract:   Contains common patch structure definitions
\*****************************************************************************/
#pragma once
#include <stdint.h>

#pragma pack( push, 1 )

namespace iOpenCL
{

const uint32_t CURRENT_ICBE_VERSION = 1051;

const uint32_t MAGIC_CL = 0x494E5443;      // 'I', 'N', 'T', 'C'
const uint32_t INVALID_INDEX = 0xFFFFFFFF;

/*****************************************************************************\
STRUCT: SProgramBinaryHeader
\*****************************************************************************/
struct SProgramBinaryHeader
{
    uint32_t   Magic;
    uint32_t   Version;

    uint32_t   Device;
    uint32_t   GPUPointerSizeInBytes;

    uint32_t   NumberOfKernels;

    uint32_t   SteppingId;

    uint32_t   PatchListSize;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SProgramBinaryHeader ) == 28 , "The size of SProgramBinaryHeader is not what is expected" );

/*****************************************************************************\
STRUCT: SKernelBinaryHeader
\*****************************************************************************/
struct SKernelBinaryHeader
{
    uint32_t   CheckSum;
    uint64_t   ShaderHashCode;
    uint32_t   KernelNameSize;
    uint32_t   PatchListSize;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SKernelBinaryHeader ) == 20 , "The size of SKernelBinaryHeader is not what is expected" );

/*****************************************************************************\
STRUCT: SKernelBinaryHeaderCommon  (used by Gen7, Gen7.5, Gen8, Gen9, Gen10)
\*****************************************************************************/
struct SKernelBinaryHeaderCommon :
       SKernelBinaryHeader
{
    uint32_t   KernelHeapSize;
    uint32_t   GeneralStateHeapSize;
    uint32_t   DynamicStateHeapSize;
    uint32_t   SurfaceStateHeapSize;
    uint32_t   KernelUnpaddedSize;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SKernelBinaryHeaderCommon ) == ( 20 + sizeof( SKernelBinaryHeader ) ) , "The size of SKernelBinaryHeaderCommon is not what is expected" );

/*****************************************************************************\
ENUM: PATCH_TOKEN
\*****************************************************************************/
enum PATCH_TOKEN
{  
    PATCH_TOKEN_UNKNOWN,                                        // 0
    PATCH_TOKEN_MEDIA_STATE_POINTERS,                           // 1    - (Unused)
    PATCH_TOKEN_STATE_SIP,                                      // 2
    PATCH_TOKEN_CS_URB_STATE,                                   // 3    - (Unused)
    PATCH_TOKEN_CONSTANT_BUFFER,                                // 4    - (Unused)
    PATCH_TOKEN_SAMPLER_STATE_ARRAY,                            // 5
    PATCH_TOKEN_INTERFACE_DESCRIPTOR,                           // 6    - (Unused)
    PATCH_TOKEN_VFE_STATE,                                      // 7    - (Unused)
    PATCH_TOKEN_BINDING_TABLE_STATE,                            // 8
    PATCH_TOKEN_ALLOCATE_SCRATCH_SURFACE,                       // 9
    PATCH_TOKEN_ALLOCATE_SIP_SURFACE,                           // 10
    PATCH_TOKEN_GLOBAL_MEMORY_OBJECT_KERNEL_ARGUMENT,           // 11   - OpenCL
    PATCH_TOKEN_IMAGE_MEMORY_OBJECT_KERNEL_ARGUMENT,            // 12   - OpenCL
    PATCH_TOKEN_CONSTANT_MEMORY_OBJECT_KERNEL_ARGUMENT,         // 13   - OpenCL
    PATCH_TOKEN_ALLOCATE_SURFACE_WITH_INITIALIZATION,           // 14
    PATCH_TOKEN_ALLOCATE_LOCAL_SURFACE,                         // 15
    PATCH_TOKEN_SAMPLER_KERNEL_ARGUMENT,                        // 16   - OpenCL
    PATCH_TOKEN_DATA_PARAMETER_BUFFER,                          // 17   - OpenCL
    PATCH_TOKEN_MEDIA_VFE_STATE,                                // 18
    PATCH_TOKEN_MEDIA_INTERFACE_DESCRIPTOR_LOAD,                // 19
    PATCH_TOKEN_MEDIA_CURBE_LOAD,                               // 20   - (Unused)
    PATCH_TOKEN_INTERFACE_DESCRIPTOR_DATA,                      // 21
    PATCH_TOKEN_THREAD_PAYLOAD,                                 // 22
    PATCH_TOKEN_EXECUTION_ENVIRONMENT,                          // 23
    PATCH_TOKEN_ALLOCATE_PRIVATE_MEMORY,                        // 24
    PATCH_TOKEN_DATA_PARAMETER_STREAM,                          // 25
    PATCH_TOKEN_KERNEL_ARGUMENT_INFO,                           // 26   - OpenCL
    PATCH_TOKEN_KERNEL_ATTRIBUTES_INFO,                         // 27   - OpenCL
    PATCH_TOKEN_STRING,                                         // 28   - OpenCL
    PATCH_TOKEN_ALLOCATE_PRINTF_SURFACE,                        // 29   - OpenCL
    PATCH_TOKEN_STATELESS_GLOBAL_MEMORY_OBJECT_KERNEL_ARGUMENT, // 30   - OpenCL
    PATCH_TOKEN_STATELESS_CONSTANT_MEMORY_OBJECT_KERNEL_ARGUMENT,//31   - OpenCL
    PATCH_TOKEN_ALLOCATE_STATELESS_SURFACE_WITH_INITIALIZATION, // 32
    PATCH_TOKEN_ALLOCATE_STATELESS_PRINTF_SURFACE,              // 33
    PATCH_TOKEN_CB_MAPPING,                                     // 34
    PATCH_TOKEN_CB2CR_GATHER_TABLE,                             // 35
    PATCH_TOKEN_ALLOCATE_STATELESS_EVENT_POOL_SURFACE,          // 36
    PATCH_TOKEN_NULL_SURFACE_LOCATION,                          // 37
    PATCH_TOKEN_ALLOCATE_STATELESS_PRIVATE_MEMORY,              // 38
    PATCH_TOKEN_ALLOCATE_CONSTANT_MEMORY_SURFACE_WITH_INITIALIZATION,           // 39
    PATCH_TOKEN_ALLOCATE_GLOBAL_MEMORY_SURFACE_WITH_INITIALIZATION,             // 40
    PATCH_TOKEN_ALLOCATE_GLOBAL_MEMORY_SURFACE_PROGRAM_BINARY_INFO,             // 41
    PATCH_TOKEN_ALLOCATE_CONSTANT_MEMORY_SURFACE_PROGRAM_BINARY_INFO,           // 42
    PATCH_TOKEN_ALLOCATE_STATELESS_GLOBAL_MEMORY_SURFACE_WITH_INITIALIZATION,   // 43
    PATCH_TOKEN_ALLOCATE_STATELESS_CONSTANT_MEMORY_SURFACE_WITH_INITIALIZATION, // 44
    PATCH_TOKEN_ALLOCATE_STATELESS_DEFAULT_DEVICE_QUEUE_SURFACE,                // 45
    PATCH_TOKEN_STATELESS_DEVICE_QUEUE_KERNEL_ARGUMENT,            // 46
    PATCH_TOKEN_GLOBAL_POINTER_PROGRAM_BINARY_INFO,                // 47
    PATCH_TOKEN_CONSTANT_POINTER_PROGRAM_BINARY_INFO,              // 48
    PATCH_TOKEN_CONSTRUCTOR_DESTRUCTOR_KERNEL_PROGRAM_BINARY_INFO, // 49
    PATCH_TOKEN_INLINE_VME_SAMPLER_INFO,                           // 50
    PATCH_TOKEN_GTPIN_FREE_GRF_INFO,                               // 51
    PATCH_TOKEN_GTPIN_INFO,

    NUM_PATCH_TOKENS
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( NUM_PATCH_TOKENS == 53, "NUM_PATCH_TOKENS has invalid value");

/*****************************************************************************\
ENUM: IMAGE_MEMORY_OBJECT_TYPE    
\*****************************************************************************/
enum IMAGE_MEMORY_OBJECT_TYPE
{
    IMAGE_MEMORY_OBJECT_INVALID,
    IMAGE_MEMORY_OBJECT_BUFFER,
    IMAGE_MEMORY_OBJECT_1D,
    IMAGE_MEMORY_OBJECT_1D_ARRAY,
    IMAGE_MEMORY_OBJECT_2D,
    IMAGE_MEMORY_OBJECT_2D_ARRAY,
    IMAGE_MEMORY_OBJECT_3D,
    IMAGE_MEMORY_OBJECT_CUBE,
    IMAGE_MEMORY_OBJECT_CUBE_ARRAY,
    IMAGE_MEMORY_OBJECT_2D_DEPTH,
    IMAGE_MEMORY_OBJECT_2D_ARRAY_DEPTH,
    IMAGE_MEMORY_OBJECT_2D_MSAA,
    IMAGE_MEMORY_OBJECT_2D_MSAA_DEPTH,
    IMAGE_MEMORY_OBJECT_2D_ARRAY_MSAA,
    IMAGE_MEMORY_OBJECT_2D_ARRAY_MSAA_DEPTH,
    IMAGE_MEMORY_OBJECT_2D_MEDIA,
    IMAGE_MEMORY_OBJECT_2D_MEDIA_BLOCK,
    NUM_IMAGE_MEMORY_OBJECT_TYPES
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( NUM_IMAGE_MEMORY_OBJECT_TYPES == 17, "NUM_IMAGE_MEMORY_OBJECT_TYPES has invalid value");

/*****************************************************************************\
ENUM: SAMPLER_OBJECT_TYPE    
\*****************************************************************************/
enum SAMPLER_OBJECT_TYPE
{
    SAMPLER_OBJECT_INVALID,
    SAMPLER_OBJECT_TEXTURE,
    SAMPLER_OBJECT_SAMPLE_8X8,
    SAMPLER_OBJECT_SAMPLE_8X8_2DCONVOLVE,
    SAMPLER_OBJECT_SAMPLE_8X8_ERODE,
    SAMPLER_OBJECT_SAMPLE_8X8_DILATE,
    SAMPLER_OBJECT_SAMPLE_8X8_MINMAXFILTER,
    SAMPLER_OBJECT_VME,
    SAMPLER_OBJECT_SAMPLE_8X8_MINMAX,
    SAMPLER_OBJECT_SAMPLE_8X8_CENTROID,
    SAMPLER_OBJECT_SAMPLE_8X8_BOOL_CENTROID,
    SAMPLER_OBJECT_SAMPLE_8X8_BOOL_SUM,
    SAMPLER_OBJECT_VE,
    SAMPLER_OBJECT_VD,
    NUM_SAMPLER_OBJECT_TYPES
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( NUM_SAMPLER_OBJECT_TYPES == 14, "NUM_SAMPLER_OBJECT_TYPES has invalid value");

/*****************************************************************************\
ENUM: DATA_PARAMETER_TOKEN
\*****************************************************************************/
enum DATA_PARAMETER_TOKEN
{
    DATA_PARAMETER_TOKEN_UNKNOWN,                                   // 0
    DATA_PARAMETER_KERNEL_ARGUMENT,                                 // 1
    DATA_PARAMETER_LOCAL_WORK_SIZE,                                 // 2
    DATA_PARAMETER_GLOBAL_WORK_SIZE,                                // 3
    DATA_PARAMETER_NUM_WORK_GROUPS,                                 // 4
    DATA_PARAMETER_WORK_DIMENSIONS,                                 // 5
    DATA_PARAMETER_LOCAL_ID,                                        // 6
    DATA_PARAMETER_EXECUTION_MASK,                                  // 7
    DATA_PARAMETER_SUM_OF_LOCAL_MEMORY_OBJECT_ARGUMENT_SIZES,       // 8
    DATA_PARAMETER_IMAGE_WIDTH,                                     // 9
    DATA_PARAMETER_IMAGE_HEIGHT,                                    // 10
    DATA_PARAMETER_IMAGE_DEPTH,                                     // 11
    DATA_PARAMETER_IMAGE_CHANNEL_DATA_TYPE,                         // 12
    DATA_PARAMETER_IMAGE_CHANNEL_ORDER,                             // 13
    DATA_PARAMETER_SAMPLER_ADDRESS_MODE,                            // 14
    DATA_PARAMETER_SAMPLER_NORMALIZED_COORDS,                       // 15
    DATA_PARAMETER_GLOBAL_WORK_OFFSET,                              // 16
    DATA_PARAMETER_NUM_HARDWARE_THREADS,                            // 17
    DATA_PARAMETER_IMAGE_ARRAY_SIZE,                                // 18
    DATA_PARAMETER_PRINTF_SURFACE_SIZE,                             // 19
    DATA_PARAMETER_IMAGE_NUM_SAMPLES,                               // 20
    DATA_PARAMETER_SAMPLER_COORDINATE_SNAP_WA_REQUIRED,             // 21
    DATA_PARAMETER_PARENT_EVENT,                                    // 22
    DATA_PARAMETER_VME_MB_BLOCK_TYPE,                               // 22
    DATA_PARAMETER_VME_SUBPIXEL_MODE,                               // 24
    DATA_PARAMETER_VME_SAD_ADJUST_MODE,                             // 25
    DATA_PARAMETER_VME_SEARCH_PATH_TYPE,                            // 26
    DATA_PARAMETER_IMAGE_NUM_MIP_LEVELS,                            // 27
    DATA_PARAMETER_ENQUEUED_LOCAL_WORK_SIZE,                        // 28
    DATA_PARAMETER_MAX_WORKGROUP_SIZE,                              // 29
    DATA_PARAMETER_PREFERRED_WORKGROUP_MULTIPLE,                    // 30
    DATA_PARAMETER_LOCAL_MEMORY_STATELESS_WINDOW_START_ADDRESS,     // 31
    DATA_PARAMETER_LOCAL_MEMORY_STATELESS_WINDOW_SIZE,              // 32
    DATA_PARAMETER_PRIVATE_MEMORY_STATELESS_SIZE,                   // 33
    DATA_PARAMETER_SIMD_SIZE,                                       // 34
    DATA_PARAMETER_OBJECT_ID,                                       // 35
    DATA_PARAMETER_VME_IMAGE_TYPE,                                  // 36
    DATA_PARAMETER_VME_MB_SKIP_BLOCK_TYPE,                          // 37
    DATA_PARAMETER_CHILD_BLOCK_SIMD_SIZE,                           // 38
    DATA_PARAMETER_IMAGE_SRGB_CHANNEL_ORDER,                        // 39
    DATA_PARAMETER_STAGE_IN_GRID_ORIGIN,                            // 40
    DATA_PARAMETER_STAGE_IN_GRID_SIZE,                              // 41
    DATA_PARAMETER_BUFFER_OFFSET,                                   // 42
    NUM_DATA_PARAMETER_TOKENS
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( NUM_DATA_PARAMETER_TOKENS == 43, "NUM_DATA_PARAMETER_TOKENS has invalid value");

/*****************************************************************************\
ENUM: CONSTANT_BUFFER_TYPE
\*****************************************************************************/
enum CONSTANT_BUFFER_TYPE
{
    CONSTANT_BUFFER_TYPE_KERNEL_ARGUMENT,
    CONSTANT_BUFFER_TYPE_INLINE,
    NUM_CONSTANT_BUFFER_TYPES
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( NUM_CONSTANT_BUFFER_TYPES == 2, "NUM_CONSTANT_BUFFER_TYPES has invalid value");

/*****************************************************************************\
ENUM: GLOBAL_BUFFER_TYPE
\*****************************************************************************/
enum GLOBAL_BUFFER_TYPE
{
    GLOBAL_BUFFER_TYPE_INLINE,
    GLOBAL_BUFFER_TYPE_INLINE_UNINIT,
    NUM_GLOBAL_BUFFER_TYPES
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( NUM_GLOBAL_BUFFER_TYPES == 2, "NUM_GLOBAL_BUFFER_TYPES has invalid value");

/*****************************************************************************\
ENUM: BUFFER_TYPES
\*****************************************************************************/
enum PROGRAM_SCOPE_BUFFER_TYPE
{
    PROGRAM_SCOPE_GLOBAL_BUFFER,
    PROGRAM_SCOPE_CONSTANT_BUFFER,
    NUM_PROGRAM_SCOPE_BUFFER_TYPE
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( NUM_PROGRAM_SCOPE_BUFFER_TYPE == 2, "NUM_PROGRAM_SCOPE_BUFFER_TYPE has invalid value");

/*****************************************************************************\
ENUM: CONSTANT_REGISTER_BOOLEAN
\*****************************************************************************/
enum CONSTANT_REGISTER_BOOLEAN
{
    CONSTANT_REGISTER_BOOLEAN_FALSE = 0x0,
    CONSTANT_REGISTER_BOOLEAN_TRUE = 0xffffffff
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( CONSTANT_REGISTER_BOOLEAN_FALSE == 0, "CONSTANT_REGISTER_BOOLEAN_FALSE has invalid value");
static_assert( CONSTANT_REGISTER_BOOLEAN_TRUE == 0xffffffff, "CONSTANT_REGISTER_BOOLEAN_TRUE has invalid value");

/*****************************************************************************\
ENUM: BUFFER_TYPES
\*****************************************************************************/
enum PROGRAM_SCOPE_KERNEL_TYPE
{
    PROGRAM_SCOPE_KERNEL_CONSTRUCTOR,
    PROGRAM_SCOPE_KERNEL_DESTRUCTOR,
    NUM_PROGRAM_SCOPE_KERNEL_TYPE
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( NUM_PROGRAM_SCOPE_KERNEL_TYPE == 2, "NUM_PROGRAM_SCOPE_KERNEL_TYPE has invalid value");

/*****************************************************************************\
STRUCT: SPatchItemHeader
\*****************************************************************************/
struct SPatchItemHeader
{
    uint32_t   Token;
    uint32_t   Size;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SPatchItemHeader ) == 8 , "The size of SPatchItemHeader is not what is expected" );

/*****************************************************************************\
STRUCT: SPatchGlobalMemoryObjectKernelArgument
\*****************************************************************************/
struct SPatchGlobalMemoryObjectKernelArgument :
       SPatchItemHeader
{
    uint32_t   ArgumentNumber;
    uint32_t   Offset;
    uint32_t   LocationIndex;
    uint32_t   LocationIndex2;
    uint32_t   IsEmulationArgument;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SPatchGlobalMemoryObjectKernelArgument ) == ( 20 + sizeof( SPatchItemHeader ) ) , "The size of SPatchGlobalMemoryObjectKernelArgument is not what is expected" );

/*****************************************************************************\
STRUCT: SPatchImageMemoryObjectKernelArgument
\*****************************************************************************/
struct SPatchImageMemoryObjectKernelArgument :
       SPatchItemHeader
{
    uint32_t  ArgumentNumber;
    uint32_t  Type;
    uint32_t  Offset;
    uint32_t  LocationIndex;
    uint32_t  LocationIndex2;

    uint32_t  Writeable;
    uint32_t  Transformable;
    uint32_t  needBindlessHandle;
    uint32_t  IsEmulationArgument;

    uint32_t  btiOffset;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SPatchImageMemoryObjectKernelArgument ) == ( 40 + sizeof( SPatchItemHeader ) ) , "The size of SPatchImageMemoryObjectKernelArgument is not what is expected" );

/*****************************************************************************\
STRUCT: SPatchConstantMemoryObjectKernelArgument
\*****************************************************************************/
struct SPatchConstantMemoryObjectKernelArgument :
       SPatchItemHeader
{
    uint32_t   ArgumentNumber;
    uint32_t   Offset;
    uint32_t   LocationIndex;
    uint32_t   LocationIndex2;
    uint32_t   IsEmulationArgument;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SPatchConstantMemoryObjectKernelArgument ) == ( 20 + sizeof( SPatchItemHeader ) ) , "The size of SPatchConstantMemoryObjectKernelArgument is not what is expected" );

/*****************************************************************************\
STRUCT: SPatchSamplerKernelArgument
\*****************************************************************************/
struct SPatchSamplerKernelArgument :
       SPatchItemHeader
{
    uint32_t   ArgumentNumber;
    uint32_t   Type;
    uint32_t   Offset;
    uint32_t   LocationIndex;
    uint32_t   LocationIndex2;
    uint32_t   needBindlessHandle;
    uint32_t   TextureMask;
    uint32_t   IsEmulationArgument;
    uint32_t   btiOffset;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SPatchSamplerKernelArgument ) == ( 36 + sizeof( SPatchItemHeader ) ) , "The size of SPatchSamplerKernelArgument is not what is expected" );

/*****************************************************************************\
STRUCT: SPatchDataParameterBuffer
\*****************************************************************************/
struct SPatchDataParameterBuffer :
       SPatchItemHeader
{
    uint32_t   Type;
    uint32_t   ArgumentNumber;
    uint32_t   Offset;
    uint32_t   DataSize;
    uint32_t   SourceOffset;
    uint32_t   LocationIndex;
    uint32_t   LocationIndex2;
    uint32_t   IsEmulationArgument;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SPatchDataParameterBuffer ) == ( 32 + sizeof( SPatchItemHeader ) ) , "The size of SPatchDataParameterBuffer is not what is expected" );

const uint32_t DATA_PARAMETER_DATA_SIZE = 4;

/*****************************************************************************\
STRUCT: SPatchKernelArgumentInfo
\*****************************************************************************/
struct SPatchKernelArgumentInfo :
       SPatchItemHeader
{
    uint32_t ArgumentNumber; 
    uint32_t AddressQualifierSize;
    uint32_t AccessQualifierSize;
    uint32_t ArgumentNameSize;
    uint32_t TypeNameSize;
    uint32_t TypeQualifierSize;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SPatchKernelArgumentInfo ) == ( 24 + sizeof( SPatchItemHeader ) ) , "The size of SPatchKernelArgumentInfo is not what is expected" );

/*****************************************************************************\
STRUCT: SPatchKernelAttributesInfo
\*****************************************************************************/
struct SPatchKernelAttributesInfo :
       SPatchItemHeader
{
    uint32_t AttributesSize;
};

// Update CURRENT_ICBE_VERSION when modifying the patch list
static_assert( sizeof( SPatchKernelAttributesInfo ) == ( 4 + sizeof( SPatchItemHeader ) ) , "The size of SPatchKernelAttributesInfo is not what is expected" );

} // namespace

#pragma pack( pop )
