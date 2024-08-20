/* #undef ALLOC_INSTRUMENTATION */
/* #undef NDEBUG */
/* #undef FDB_RELEASE */
#ifdef FDB_RELEASE
# define FDB_CLEAN_BUILD
#endif // FDB_RELEASE
/* #undef OPEN_FOR_IDE */
#define FDB_SOURCE_DIR "/Users/gyming/Documents/USC/CATPS/Task/foundationdb"
#define FDB_BINARY_DIR "/Users/gyming/Documents/USC/CATPS/Task/build"
#ifdef WIN32
# define _WIN32_WINNT 
# define WINVER 
# define NTDDI_VERSION 0x05020000
# define BOOST_ALL_NO_LIB
#else
/* #undef USE_ASAN */
/* #undef USE_MSAN */
/* #undef USE_UBSAN */
/* #undef USE_TSAN */
# if defined(USE_ASAN) || \
     defined(USE_MSAN) || \
     defined(USE_UBSAN) || \
     defined(USE_TSAN)
#  define USE_SANITIZER
# endif
/* #undef USE_GCOV */
/* #undef USE_VALGRIND */
# ifdef USE_VALGRIND
#  define VALGRIND 1
# endif
/* #undef DTRACE_PROBES */
# define HAS_ALIGNED_ALLOC
/* #undef USE_JEMALLOC */
#endif // WIN32
