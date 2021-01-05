file(GLOB ROOT_SOURCE ./include/glm/*.cpp)
file(GLOB ROOT_INLINE ./include/glm/*.inl)
file(GLOB ROOT_HEADER ./include/glm/*.hpp)
# file(GLOB ROOT_TEXT ../*.txt)
# file(GLOB ROOT_MD ../*.md)
# file(GLOB ROOT_NAT ../util/glm.natvis)

file(GLOB_RECURSE CORE_SOURCE ./include/glm/detail/*.cpp)
file(GLOB_RECURSE CORE_INLINE ./include/glm/detail/*.inl)
file(GLOB_RECURSE CORE_HEADER ./include/glm/detail/*.hpp)

file(GLOB_RECURSE EXT_SOURCE ./include/glm/ext/*.cpp)
file(GLOB_RECURSE EXT_INLINE ./include/glm/ext/*.inl)
file(GLOB_RECURSE EXT_HEADER ./include/glm/ext/*.hpp)

file(GLOB_RECURSE GTC_SOURCE ./include/glm/gtc/*.cpp)
file(GLOB_RECURSE GTC_INLINE ./include/glm/gtc/*.inl)
file(GLOB_RECURSE GTC_HEADER ./include/glm/gtc/*.hpp)

file(GLOB_RECURSE GTX_SOURCE ./include/glm/gtx/*.cpp)
file(GLOB_RECURSE GTX_INLINE ./include/glm/gtx/*.inl)
file(GLOB_RECURSE GTX_HEADER ./include/glm/gtx/*.hpp)

file(GLOB_RECURSE SIMD_SOURCE ./include/glm/simd/*.cpp)
file(GLOB_RECURSE SIMD_INLINE ./include/glm/simd/*.inl)
file(GLOB_RECURSE SIMD_HEADER ./include/glm/simd/*.h)

source_group("Text Files" FILES ${ROOT_TEXT} ${ROOT_MD})
source_group("Core Files" FILES ${CORE_SOURCE})
source_group("Core Files" FILES ${CORE_INLINE})
source_group("Core Files" FILES ${CORE_HEADER})
source_group("EXT Files" FILES ${EXT_SOURCE})
source_group("EXT Files" FILES ${EXT_INLINE})
source_group("EXT Files" FILES ${EXT_HEADER})
source_group("GTC Files" FILES ${GTC_SOURCE})
source_group("GTC Files" FILES ${GTC_INLINE})
source_group("GTC Files" FILES ${GTC_HEADER})
source_group("GTX Files" FILES ${GTX_SOURCE})
source_group("GTX Files" FILES ${GTX_INLINE})
source_group("GTX Files" FILES ${GTX_HEADER})
source_group("SIMD Files" FILES ${SIMD_SOURCE})
source_group("SIMD Files" FILES ${SIMD_INLINE})
source_group("SIMD Files" FILES ${SIMD_HEADER})

add_library(glm INTERFACE)
target_include_directories(glm SYSTEM INTERFACE ./include)

if(BUILD_STATIC_LIBS)
add_library(glm_static STATIC ${ROOT_TEXT} ${ROOT_MD} ${ROOT_NAT}
	${ROOT_SOURCE}    ${ROOT_INLINE}    ${ROOT_HEADER}
	${CORE_SOURCE}    ${CORE_INLINE}    ${CORE_HEADER}
	${EXT_SOURCE}     ${EXT_INLINE}     ${EXT_HEADER}
	${GTC_SOURCE}     ${GTC_INLINE}     ${GTC_HEADER}
	${GTX_SOURCE}     ${GTX_INLINE}     ${GTX_HEADER}
	${SIMD_SOURCE}    ${SIMD_INLINE}    ${SIMD_HEADER})
endif()

if(BUILD_SHARED_LIBS)
add_library(glm_shared SHARED ${ROOT_TEXT} ${ROOT_MD} ${ROOT_NAT}
	${ROOT_SOURCE}    ${ROOT_INLINE}    ${ROOT_HEADER}
	${CORE_SOURCE}    ${CORE_INLINE}    ${CORE_HEADER}
	${EXT_SOURCE}     ${EXT_INLINE}     ${EXT_HEADER}
	${GTC_SOURCE}     ${GTC_INLINE}     ${GTC_HEADER}
	${GTX_SOURCE}     ${GTX_INLINE}     ${GTX_HEADER}
	${SIMD_SOURCE}    ${SIMD_INLINE}    ${SIMD_HEADER})
endif()

