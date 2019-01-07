project(codec2)
#
# Generated sources
#

set( CMAKE_VERBOSE_MAKEFILE ON )
set(D ${CMAKE_CURRENT_SOURCE_DIR}/codebook)

# Math library is automatic on windows
if(UNIX)
    set(CMAKE_REQUIRED_INCLUDES math.h)
    set(CMAKE_REQUIRED_LIBRARIES m)
endif(UNIX)

include(CheckIncludeFiles)
check_include_files("stdlib.h" HAVE_STDLIB_H)
check_include_files("string.h" HAVE_STRING_H)

include(CheckFunctionExists)
check_function_exists(floor  HAVE_FLOOR)
check_function_exists(ceil   HAVE_CEIL)
check_function_exists(pow    HAVE_POW)
check_function_exists(sqrt   HAVE_SQRT)
check_function_exists(sin    HAVE_SIN)
check_function_exists(cos    HAVE_COS)
check_function_exists(atan2  HAVE_ATAN2)
check_function_exists(log10  HAVE_LOG10)
check_function_exists(round  HAVE_ROUND)
check_function_exists(getopt HAVE_GETOPT)


#[[
# lsp quantisers

set(CODEBOOKS
    ${D}/lsp1.txt
    ${D}/lsp2.txt
    ${D}/lsp3.txt
    ${D}/lsp4.txt
    ${D}/lsp5.txt
    ${D}/lsp6.txt
    ${D}/lsp7.txt
    ${D}/lsp8.txt
    ${D}/lsp9.txt
    ${D}/lsp10.txt
)

# lspd quantisers

set(CODEBOOKSD
    ${D}/dlsp1.txt
    ${D}/dlsp2.txt
    ${D}/dlsp3.txt
    ${D}/dlsp4.txt
    ${D}/dlsp5.txt
    ${D}/dlsp6.txt
    ${D}/dlsp7.txt
    ${D}/dlsp8.txt
    ${D}/dlsp9.txt
    ${D}/dlsp10.txt
)

set(CODEBOOKSJVM
    ${D}/lspjvm1.txt
    ${D}/lspjvm2.txt
    ${D}/lspjvm3.txt
)

set(CODEBOOKSMEL
    ${D}/mel1.txt
    ${D}/mel2.txt
    ${D}/mel3.txt
    ${D}/mel4.txt
    ${D}/mel5.txt
    ${D}/mel6.txt
)

set(CODEBOOKSLSPMELVQ
    ${D}/lspmelvq1.txt
    ${D}/lspmelvq2.txt
    ${D}/lspmelvq3.txt
)

set(CODEBOOKSGE ${D}/gecb.txt)

set(CODEBOOKSNEWAMP1
    ${D}/train_120_1.txt
    ${D}/train_120_2.txt
)

set(CODEBOOKSNEWAMP1_ENERGY
    ${D}/newamp1_energy_q.txt
)

set(CODEBOOKSNEWAMP2
    ${D}/codes_450.txt
)

set(CODEBOOKSNEWAMP2_ENERGY
    ${D}/newamp2_energy_q.txt
)


# generated wideband map
set(C2WB_MAP
    ${D}/c2wideband_map.txt
)


# when crosscompiling we need a native executable

if(CMAKE_CROSSCOMPILING)
    include(ExternalProject)
    ExternalProject_Add(codec2_native
       SOURCE_DIR ${CMAKE_SOURCE_DIR}
       BUILD_COMMAND $(MAKE) generate_codebook
       INSTALL_COMMAND ${CMAKE_COMMAND} -E copy src/generate_codebook ${CMAKE_CURRENT_BINARY_DIR}
    )
    add_executable(generate_codebook IMPORTED)
    set_target_properties(generate_codebook PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/generate_codebook)
    add_dependencies(generate_codebook codec2_native)
else(CMAKE_CROSSCOMPILING)
# Build code generator binaries. These do not get installed.
    # generate_codebook
    add_executable(generate_codebook generate_codebook.c)
    target_link_libraries(generate_codebook ${CMAKE_REQUIRED_LIBRARIES})
    # Make native builds available for cross-compiling.
    export(TARGETS generate_codebook
        FILE ${CMAKE_BINARY_DIR}/ImportExecutables.cmake)
endif(CMAKE_CROSSCOMPILING)


# codebook.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebook.c
    COMMAND generate_codebook lsp_cb ${CODEBOOKS} > ${CMAKE_CURRENT_BINARY_DIR}/codebook.c
    DEPENDS generate_codebook ${CODEBOOKS}
)

# codebookd.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebookd.c
    COMMAND generate_codebook lsp_cbd ${CODEBOOKSD} > ${CMAKE_CURRENT_BINARY_DIR}/codebookd.c
    DEPENDS generate_codebook ${CODEBOOKSD}
)

# codebookjvm.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebookjvm.c
    COMMAND generate_codebook lsp_cbjvm ${CODEBOOKSJVM} > ${CMAKE_CURRENT_BINARY_DIR}/codebookjvm.c
    DEPENDS generate_codebook ${CODEBOOKSJVM}
)


# codebookmel.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebookmel.c
    COMMAND generate_codebook mel_cb ${CODEBOOKSMEL} > ${CMAKE_CURRENT_BINARY_DIR}/codebookmel.c
    DEPENDS generate_codebook ${CODEBOOKSMEL}
)

# codebooklspmelvq.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebooklspmelvq.c
    COMMAND generate_codebook lspmelvq_cb ${CODEBOOKSLSPMELVQ} > ${CMAKE_CURRENT_BINARY_DIR}/codebooklspmelvq.c
    DEPENDS generate_codebook ${CODEBOOKSLSPMELVQ}
)

# codebookge.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebookge.c
    COMMAND generate_codebook ge_cb ${CODEBOOKSGE} > ${CMAKE_CURRENT_BINARY_DIR}/codebookge.c
    DEPENDS generate_codebook ${CODEBOOKSGE}
)

# codebooknewamp1.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebooknewamp1.c
    COMMAND generate_codebook newamp1vq_cb ${CODEBOOKSNEWAMP1} > ${CMAKE_CURRENT_BINARY_DIR}/codebooknewamp1.c
    DEPENDS generate_codebook ${CODEBOOKSNEWAMP1}
)

# codebooknewamp1_energy.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebooknewamp1_energy.c
    COMMAND generate_codebook newamp1_energy_cb ${CODEBOOKSNEWAMP1_ENERGY} > ${CMAKE_CURRENT_BINARY_DIR}/codebooknewamp1_energy.c
    DEPENDS generate_codebook ${CODEBOOKSNEWAMP1_ENERGY}
)

# codebooknewamp2.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebooknewamp2.c
    COMMAND generate_codebook newamp2vq_cb ${CODEBOOKSNEWAMP2} > ${CMAKE_CURRENT_BINARY_DIR}/codebooknewamp2.c
    DEPENDS generate_codebook ${CODEBOOKSNEWAMP2}
)

# codebooknewamp2_energy.c
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/codebooknewamp2_energy.c
    COMMAND generate_codebook newamp2_energy_cb ${CODEBOOKSNEWAMP2_ENERGY} > ${CMAKE_CURRENT_BINARY_DIR}/codebooknewamp2_energy.c
    DEPENDS generate_codebook ${CODEBOOKSNEWAMP2_ENERGY}
)



# when crosscompiling we need a native executable
if(CMAKE_CROSSCOMPILING)
    # Native executable already built above.
    add_executable(generate_wideband_map IMPORTED)
    set_target_properties(generate_wideband_map PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/generate_wideband_map)
    add_dependencies(generate_wideband_map codec2_native)
else(CMAKE_CROSSCOMPILING)
# Build code generator binaries. These do not get installed.
    # generate_codebook
    add_executable(generate_wideband_map generate_wideband_map.c)
    target_link_libraries(generate_wideband_map ${CMAKE_REQUIRED_LIBRARIES})
    # Make native builds available for cross-compiling.
    export(TARGETS generate_wideband_map
        FILE ${CMAKE_BINARY_DIR}/ImportExecutables.cmake)
endif(CMAKE_CROSSCOMPILING)



# c2wideband_map.h
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/c2wideband_map.h
    COMMAND generate_wideband_map c2wideband_map ${C2WB_MAP} > ${CMAKE_CURRENT_BINARY_DIR}/c2wideband_map.h
    DEPENDS generate_wideband_map ${C2WB_MAP}
)

]]#


#
# codec2 library sources
#

set(CODEC2_SRCS
    dump.c
    lpc.c
    nlp.c
    postfilter.c
    sine.c
    codec2.c
    codec2_fft.c
    cohpsk.c
    fifo.c
    fdmdv.c
    fm.c
    fsk.c
    fmfsk.c
    tdma.c
    kiss_fft.c
    kiss_fftr.c
    linreg.c
    interp.c
    lsp.c
    mbest.c
    newamp1.c
    newamp2.c
    ofdm.c
    phase.c
    quantise.c
    pack.c
    codebook.c
    codebookd.c
    codebookjvm.c
    codebookmel.c
    codebooklspmelvq.c
    codebookge.c
    codebooknewamp1.c
    codebooknewamp1_energy.c
    codebooknewamp2.c
    codebooknewamp2_energy.c
    golay23.c
    freedv_api.c
    freedv_vhf_framing.c
    freedv_data_channel.c
    varicode.c
    modem_stats.c
    c2wideband.c
    dct2.c
    ofdm.c
    mpdecode_core.c
    phi0.c
    gp_interleaver.c
    interldpc.c
    filter.c
    #horus_api.c
    #horus_l2.c
)

set(CODEC2_PUBLIC_HEADERS
    golay23.h
    codec2.h
    codec2_fdmdv.h
    codec2_cohpsk.h
    codec2_fm.h
    codec2_ofdm.h
    fsk.h
    codec2_fifo.h
    comp.h
    comp_prim.h
    modem_stats.h
    kiss_fft.h
    freedv_api.h
    varicode.h
    freedv_api_internal.h
    filter.h
    horus_api.h
    ${CODEC2_VERSION_PATH}/version.h
)

#
# Setup the codec2 library
#
add_library(codec2 SHARED ${CODEC2_SRCS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(codec2 ${CMAKE_REQUIRED_LIBRARIES})
set(SOVERSION "0.8")
set_target_properties(codec2 PROPERTIES
    SOVERSION ${SOVERSION}
    PUBLIC_HEADER "${CODEC2_PUBLIC_HEADERS}"
)

