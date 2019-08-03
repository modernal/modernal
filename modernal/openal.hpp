#ifndef AL_AL_H
#define AL_AL_H

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_WIN32) && !defined(_XBOX)
#if defined(AL_BUILD_LIBRARY) || defined (_OPENAL32LIB)
#define AL_API __declspec(dllexport)
#else
#define AL_API __declspec(dllimport)
#endif
#else
#define AL_API extern
#endif

#if defined(_WIN32)
#define AL_APIENTRY __cdecl
#else
#define AL_APIENTRY
#endif

#if TARGET_OS_MAC
#pragma export on
#endif

#define OPENAL
#define ALAPI AL_API
#define ALAPIENTRY AL_APIENTRY
#define AL_VERSION_1_0
#define AL_VERSION_1_1

typedef char ALboolean;
typedef char ALchar;
typedef char ALbyte;
typedef unsigned char ALubyte;
typedef short ALshort;
typedef unsigned short ALushort;
typedef int ALint;
typedef unsigned int ALuint;
typedef int ALsizei;
typedef int ALenum;
typedef float ALfloat;
typedef double ALdouble;
typedef void ALvoid;

#define AL_INVALID -1
#define AL_NONE 0
#define AL_FALSE 0
#define AL_TRUE 1
#define AL_SOURCE_RELATIVE 0x202
#define AL_CONE_INNER_ANGLE 0x1001
#define AL_CONE_OUTER_ANGLE 0x1002
#define AL_PITCH 0x1003
#define AL_POSITION 0x1004
#define AL_DIRECTION 0x1005
#define AL_VELOCITY 0x1006
#define AL_LOOPING 0x1007
#define AL_BUFFER 0x1009
#define AL_GAIN 0x100A
#define AL_MIN_GAIN 0x100D
#define AL_MAX_GAIN 0x100E
#define AL_ORIENTATION 0x100F
#define AL_CHANNEL_MASK 0x3000
#define AL_SOURCE_STATE 0x1010
#define AL_INITIAL 0x1011
#define AL_PLAYING 0x1012
#define AL_PAUSED 0x1013
#define AL_STOPPED 0x1014
#define AL_BUFFERS_QUEUED 0x1015
#define AL_BUFFERS_PROCESSED 0x1016
#define AL_SEC_OFFSET 0x1024
#define AL_SAMPLE_OFFSET 0x1025
#define AL_BYTE_OFFSET 0x1026
#define AL_SOURCE_TYPE 0x1027
#define AL_STATIC 0x1028
#define AL_STREAMING 0x1029
#define AL_UNDETERMINED 0x1030
#define AL_FORMAT_MONO8 0x1100
#define AL_FORMAT_MONO16 0x1101
#define AL_FORMAT_STEREO8 0x1102
#define AL_FORMAT_STEREO16 0x1103
#define AL_REFERENCE_DISTANCE 0x1020
#define AL_ROLLOFF_FACTOR 0x1021
#define AL_CONE_OUTER_GAIN 0x1022
#define AL_MAX_DISTANCE 0x1023
#define AL_FREQUENCY 0x2001
#define AL_BITS 0x2002
#define AL_CHANNELS 0x2003
#define AL_SIZE 0x2004
#define AL_UNUSED 0x2010
#define AL_PENDING 0x2011
#define AL_PROCESSED 0x2012
#define AL_NO_ERROR AL_FALSE
#define AL_INVALID_NAME 0xA001
#define AL_ILLEGAL_ENUM 0xA002
#define AL_INVALID_ENUM 0xA002
#define AL_INVALID_VALUE 0xA003
#define AL_ILLEGAL_COMMAND 0xA004
#define AL_INVALID_OPERATION 0xA004
#define AL_OUT_OF_MEMORY 0xA005
#define AL_VENDOR 0xB001
#define AL_VERSION 0xB002
#define AL_RENDERER 0xB003
#define AL_EXTENSIONS 0xB004
#define AL_DOPPLER_FACTOR 0xC000
#define AL_DOPPLER_VELOCITY 0xC001
#define AL_SPEED_OF_SOUND 0xC003
#define AL_DISTANCE_MODEL 0xD000
#define AL_INVERSE_DISTANCE 0xD001
#define AL_INVERSE_DISTANCE_CLAMPED 0xD002
#define AL_LINEAR_DISTANCE 0xD003
#define AL_LINEAR_DISTANCE_CLAMPED 0xD004
#define AL_EXPONENT_DISTANCE 0xD005
#define AL_EXPONENT_DISTANCE_CLAMPED 0xD006

typedef void (AL_APIENTRY *LPALENABLE)( ALenum capability );
typedef void (AL_APIENTRY *LPALDISABLE)( ALenum capability );
typedef ALboolean (AL_APIENTRY *LPALISENABLED)( ALenum capability );
typedef const ALchar* (AL_APIENTRY *LPALGETSTRING)( ALenum param );
typedef void (AL_APIENTRY *LPALGETBOOLEANV)( ALenum param, ALboolean* data );
typedef void (AL_APIENTRY *LPALGETINTEGERV)( ALenum param, ALint* data );
typedef void (AL_APIENTRY *LPALGETFLOATV)( ALenum param, ALfloat* data );
typedef void (AL_APIENTRY *LPALGETDOUBLEV)( ALenum param, ALdouble* data );
typedef ALboolean (AL_APIENTRY *LPALGETBOOLEAN)( ALenum param );
typedef ALint (AL_APIENTRY *LPALGETINTEGER)( ALenum param );
typedef ALfloat (AL_APIENTRY *LPALGETFLOAT)( ALenum param );
typedef ALdouble (AL_APIENTRY *LPALGETDOUBLE)( ALenum param );
typedef ALenum (AL_APIENTRY *LPALGETERROR)( void );
typedef ALboolean (AL_APIENTRY *LPALISEXTENSIONPRESENT)(const ALchar* extname );
typedef void* (AL_APIENTRY *LPALGETPROCADDRESS)( const ALchar* fname );
typedef ALenum (AL_APIENTRY *LPALGETENUMVALUE)( const ALchar* ename );
typedef void (AL_APIENTRY *LPALLISTENERF)( ALenum param, ALfloat value );
typedef void (AL_APIENTRY *LPALLISTENER3F)( ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void (AL_APIENTRY *LPALLISTENERFV)( ALenum param, const ALfloat* values );
typedef void (AL_APIENTRY *LPALLISTENERI)( ALenum param, ALint value );
typedef void (AL_APIENTRY *LPALLISTENER3I)( ALenum param, ALint value1, ALint value2, ALint value3 );
typedef void (AL_APIENTRY *LPALLISTENERIV)( ALenum param, const ALint* values );
typedef void (AL_APIENTRY *LPALGETLISTENERF)( ALenum param, ALfloat* value );
typedef void (AL_APIENTRY *LPALGETLISTENER3F)( ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3 );
typedef void (AL_APIENTRY *LPALGETLISTENERFV)( ALenum param, ALfloat* values );
typedef void (AL_APIENTRY *LPALGETLISTENERI)( ALenum param, ALint* value );
typedef void (AL_APIENTRY *LPALGETLISTENER3I)( ALenum param, ALint *value1, ALint *value2, ALint *value3 );
typedef void (AL_APIENTRY *LPALGETLISTENERIV)( ALenum param, ALint* values );
typedef void (AL_APIENTRY *LPALGENSOURCES)( ALsizei n, ALuint* sources );
typedef void (AL_APIENTRY *LPALDELETESOURCES)( ALsizei n, const ALuint* sources );
typedef ALboolean (AL_APIENTRY *LPALISSOURCE)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCEF)( ALuint sid, ALenum param, ALfloat value);
typedef void (AL_APIENTRY *LPALSOURCE3F)( ALuint sid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void (AL_APIENTRY *LPALSOURCEFV)( ALuint sid, ALenum param, const ALfloat* values );
typedef void (AL_APIENTRY *LPALSOURCEI)( ALuint sid, ALenum param, ALint value);
typedef void (AL_APIENTRY *LPALSOURCE3I)( ALuint sid, ALenum param, ALint value1, ALint value2, ALint value3 );
typedef void (AL_APIENTRY *LPALSOURCEIV)( ALuint sid, ALenum param, const ALint* values );
typedef void (AL_APIENTRY *LPALGETSOURCEF)( ALuint sid, ALenum param, ALfloat* value );
typedef void (AL_APIENTRY *LPALGETSOURCE3F)( ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
typedef void (AL_APIENTRY *LPALGETSOURCEFV)( ALuint sid, ALenum param, ALfloat* values );
typedef void (AL_APIENTRY *LPALGETSOURCEI)( ALuint sid, ALenum param, ALint* value );
typedef void (AL_APIENTRY *LPALGETSOURCE3I)( ALuint sid, ALenum param, ALint* value1, ALint* value2, ALint* value3);
typedef void (AL_APIENTRY *LPALGETSOURCEIV)( ALuint sid, ALenum param, ALint* values );
typedef void (AL_APIENTRY *LPALSOURCEPLAYV)( ALsizei ns, const ALuint *sids );
typedef void (AL_APIENTRY *LPALSOURCESTOPV)( ALsizei ns, const ALuint *sids );
typedef void (AL_APIENTRY *LPALSOURCEREWINDV)( ALsizei ns, const ALuint *sids );
typedef void (AL_APIENTRY *LPALSOURCEPAUSEV)( ALsizei ns, const ALuint *sids );
typedef void (AL_APIENTRY *LPALSOURCEPLAY)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCESTOP)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCEREWIND)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCEPAUSE)( ALuint sid );
typedef void (AL_APIENTRY *LPALSOURCEQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, const ALuint *bids );
typedef void (AL_APIENTRY *LPALSOURCEUNQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, ALuint *bids );
typedef void (AL_APIENTRY *LPALGENBUFFERS)( ALsizei n, ALuint* buffers );
typedef void (AL_APIENTRY *LPALDELETEBUFFERS)( ALsizei n, const ALuint* buffers );
typedef ALboolean (AL_APIENTRY *LPALISBUFFER)( ALuint bid );
typedef void (AL_APIENTRY *LPALBUFFERDATA)( ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq );
typedef void (AL_APIENTRY *LPALBUFFERF)( ALuint bid, ALenum param, ALfloat value);
typedef void (AL_APIENTRY *LPALBUFFER3F)( ALuint bid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void (AL_APIENTRY *LPALBUFFERFV)( ALuint bid, ALenum param, const ALfloat* values );
typedef void (AL_APIENTRY *LPALBUFFERI)( ALuint bid, ALenum param, ALint value);
typedef void (AL_APIENTRY *LPALBUFFER3I)( ALuint bid, ALenum param, ALint value1, ALint value2, ALint value3 );
typedef void (AL_APIENTRY *LPALBUFFERIV)( ALuint bid, ALenum param, const ALint* values );
typedef void (AL_APIENTRY *LPALGETBUFFERF)( ALuint bid, ALenum param, ALfloat* value );
typedef void (AL_APIENTRY *LPALGETBUFFER3F)( ALuint bid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
typedef void (AL_APIENTRY *LPALGETBUFFERFV)( ALuint bid, ALenum param, ALfloat* values );
typedef void (AL_APIENTRY *LPALGETBUFFERI)( ALuint bid, ALenum param, ALint* value );
typedef void (AL_APIENTRY *LPALGETBUFFER3I)( ALuint bid, ALenum param, ALint* value1, ALint* value2, ALint* value3);
typedef void (AL_APIENTRY *LPALGETBUFFERIV)( ALuint bid, ALenum param, ALint* values );
typedef void (AL_APIENTRY *LPALDOPPLERFACTOR)( ALfloat value );
typedef void (AL_APIENTRY *LPALDOPPLERVELOCITY)( ALfloat value );
typedef void (AL_APIENTRY *LPALSPEEDOFSOUND)( ALfloat value );
typedef void (AL_APIENTRY *LPALDISTANCEMODEL)( ALenum distanceModel );

#if TARGET_OS_MAC
#pragma export off
#endif

#if defined(__cplusplus)
}
#endif

#endif

#ifndef AL_ALC_H
#define AL_ALC_H

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_WIN32) && !defined(_XBOX)

#if defined(AL_BUILD_LIBRARY) || defined (_OPENAL32LIB)
#define ALC_API __declspec(dllexport)
#else
#define ALC_API __declspec(dllimport)
#endif
#else
#if defined(AL_BUILD_LIBRARY) && defined(HAVE_GCC_VISIBILITY)
#define ALC_API __attribute__((visibility("default")))
#else
#define ALC_API extern
#endif
#endif

#if defined(_WIN32)
#define ALC_APIENTRY __cdecl
#else
#define ALC_APIENTRY
#endif

#if defined(TARGET_OS_MAC) && TARGET_OS_MAC
#pragma export on
#endif

#define ALCAPI ALC_API
#define ALCAPIENTRY ALC_APIENTRY
#define ALC_INVALID 0

#define ALC_VERSION_0_1 1

typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;

typedef char ALCboolean;
typedef char ALCchar;
typedef char ALCbyte;
typedef unsigned char ALCubyte;
typedef short ALCshort;
typedef unsigned short ALCushort;
typedef int ALCint;
typedef unsigned int ALCuint;
typedef int ALCsizei;
typedef int ALCenum;
typedef float ALCfloat;
typedef double ALCdouble;
typedef void ALCvoid;

#define ALC_FALSE 0
#define ALC_TRUE 1
#define ALC_FREQUENCY 0x1007
#define ALC_REFRESH 0x1008
#define ALC_SYNC 0x1009
#define ALC_MONO_SOURCES 0x1010
#define ALC_STEREO_SOURCES 0x1011
#define ALC_NO_ERROR ALC_FALSE
#define ALC_INVALID_DEVICE 0xA001
#define ALC_INVALID_CONTEXT 0xA002
#define ALC_INVALID_ENUM 0xA003
#define ALC_INVALID_VALUE 0xA004
#define ALC_OUT_OF_MEMORY 0xA005
#define ALC_DEFAULT_DEVICE_SPECIFIER 0x1004
#define ALC_DEVICE_SPECIFIER 0x1005
#define ALC_EXTENSIONS 0x1006
#define ALC_MAJOR_VERSION 0x1000
#define ALC_MINOR_VERSION 0x1001
#define ALC_ATTRIBUTES_SIZE 0x1002
#define ALC_ALL_ATTRIBUTES 0x1003
#define ALC_DEFAULT_ALL_DEVICES_SPECIFIER 0x1012
#define ALC_ALL_DEVICES_SPECIFIER 0x1013
#define ALC_CAPTURE_DEVICE_SPECIFIER 0x310
#define ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER 0x311
#define ALC_CAPTURE_SAMPLES 0x312

typedef ALCcontext * (ALC_APIENTRY *LPALCCREATECONTEXT) (ALCdevice *device, const ALCint *attrlist);
typedef ALCboolean (ALC_APIENTRY *LPALCMAKECONTEXTCURRENT)( ALCcontext *context );
typedef void (ALC_APIENTRY *LPALCPROCESSCONTEXT)( ALCcontext *context );
typedef void (ALC_APIENTRY *LPALCSUSPENDCONTEXT)( ALCcontext *context );
typedef void (ALC_APIENTRY *LPALCDESTROYCONTEXT)( ALCcontext *context );
typedef ALCcontext * (ALC_APIENTRY *LPALCGETCURRENTCONTEXT)( void );
typedef ALCdevice * (ALC_APIENTRY *LPALCGETCONTEXTSDEVICE)( ALCcontext *context );
typedef ALCdevice * (ALC_APIENTRY *LPALCOPENDEVICE)( const ALCchar *devicename );
typedef ALCboolean (ALC_APIENTRY *LPALCCLOSEDEVICE)( ALCdevice *device );
typedef ALCenum (ALC_APIENTRY *LPALCGETERROR)( ALCdevice *device );
typedef ALCboolean (ALC_APIENTRY *LPALCISEXTENSIONPRESENT)( ALCdevice *device, const ALCchar *extname );
typedef void * (ALC_APIENTRY *LPALCGETPROCADDRESS)(ALCdevice *device, const ALCchar *funcname );
typedef ALCenum (ALC_APIENTRY *LPALCGETENUMVALUE)(ALCdevice *device, const ALCchar *enumname );
typedef const ALCchar* (ALC_APIENTRY *LPALCGETSTRING)( ALCdevice *device, ALCenum param );
typedef void (ALC_APIENTRY *LPALCGETINTEGERV)( ALCdevice *device, ALCenum param, ALCsizei size, ALCint *dest );
typedef ALCdevice * (ALC_APIENTRY *LPALCCAPTUREOPENDEVICE)( const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize );
typedef ALCboolean (ALC_APIENTRY *LPALCCAPTURECLOSEDEVICE)( ALCdevice *device );
typedef void (ALC_APIENTRY *LPALCCAPTURESTART)( ALCdevice *device );
typedef void (ALC_APIENTRY *LPALCCAPTURESTOP)( ALCdevice *device );
typedef void (ALC_APIENTRY *LPALCCAPTURESAMPLES)( ALCdevice *device, ALCvoid *buffer, ALCsizei samples );

#if defined(TARGET_OS_MAC) && TARGET_OS_MAC
#pragma export off
#endif

#if defined(__cplusplus)
}
#endif

#endif
