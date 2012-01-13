noinst_HEADERS +=\
	common/autoptr.h\
	common/bitstream.h\
	common/closefrom.h\
	common/debuglog.h\
	common/fd.h\
	common/filetests.h\
	common/fileutils.h\
	common/gnu_getopt.h\
	common/internaltypes.h\
	common/io_utils.h\
	common/msvc_dirent.h\
	common/msvc_posix_wrapper.h\
	common/noreturn.h\
	common/omassert.h\
	common/output.h\
	common/output-internal.h\
	common/pack.h\
	common/pretty.h\
	common/realtime.h\
	common/registryinternal.h\
	common/remoteprotocol.h\
	common/replicate_utils.h\
	common/replicationprotocol.h\
	common/safedirent.h\
	common/safeerrno.h\
	common/safefcntl.h\
	common/safesysselect.h\
	common/safesysstat.h\
	common/safesyswait.h\
	common/safeunistd.h\
	common/safeuuid.h\
	common/safewindows.h\
	common/safewinsock2.h\
	common/serialise-double.h\
	common/socket_utils.h\
	common/str.h\
	common/stringutils.h\
	common/submatch.h\
	common/unaligned.h

EXTRA_DIST +=\
	common/dir_contents\
	common/win32_uuid.cc\
	common/win32_uuid.h\
	common/Makefile

lib_src +=\
	common/bitstream.cc\
	common/closefrom.cc\
	common/debuglog.cc\
	common/fileutils.cc\
	common/io_utils.cc\
	common/msvc_dirent.cc\
	common/msvc_posix_wrapper.cc\
	common/omassert.cc\
	common/replicate_utils.cc\
	common/safe.cc\
	common/serialise-double.cc\
	common/socket_utils.cc\
	common/str.cc\
	common/stringutils.cc

if USE_WIN32_UUID_API
lib_src +=\
	common/win32_uuid.cc
libxapian_la_LDFLAGS += -lrpcrt4
endif

noinst_LTLIBRARIES += libgetopt.la

libgetopt_la_SOURCES =\
	common/getopt.cc
