#include <Python.h>
#include <structmember.h>

#include "openal.hpp"

#if defined(_WIN32) || defined(_WIN64)

#include <Windows.h>

void * _load_al_method_raw(void * libal, const char * method) {
    return (void *)GetProcAddress((HMODULE)libal, method);
}

#define load_al_method_raw(libal, method) _load_al_method_raw(libal, method)
#define load_al_library(name) LoadLibrary(name);
#define DEFAULT_LIBAL "openal32.dll"

#elif defined(__APPLE__)

#import <mach-o/dyld.h>
#import <stdlib.h>
#import <string.h>

void * _load_al_method_raw(const char * method) {
    NSSymbol symbol = 0;

    if (NSIsSymbolNameDefined(method)) {
        symbol = NSLookupAndBindSymbol(method);
    }

    return symbol ? NSAddressOfSymbol(symbol) : NULL;
}

#define load_al_method_raw(libal, method) _load_al_method_raw("_" method)
#define load_al_library(name) "OpenAL"
#define DEFAULT_LIBAL "OpenAL"

#else

#include <dlfcn.h>

void * _load_al_method_raw(void * libal, const char * method) {
    return (void *)dlsym(libal, method);
}

#define load_al_method_raw(libal, method) _load_al_method_raw(libal, method)
#define load_al_library(name) dlopen(name, RTLD_LAZY);
#define DEFAULT_LIBAL "libopenal.so"

#endif

void * load_al_method(void * libal, const char * name) {
    if (PyErr_Occurred()) {
        return NULL;
    }
    void * res = load_al_method_raw(libal, name);
    if (!res) {
        PyErr_Format(PyExc_Exception, "%s not found", name);
    }
    return res;
}

inline int py_floats(float * ptr, int min, int max, PyObject * tup) {
    PyObject * seq = PySequence_Fast(tup, "not iterable");
    if (!seq) {
        return -1;
    }
    int size = (int)PySequence_Fast_GET_SIZE(seq);
    if (size < min || size > max) {
        return -1;
    }
    for (int i = 0; i < size; ++i) {
        ptr[i] = (float)PyFloat_AsDouble(PySequence_Fast_GET_ITEM(seq, i));
    }
    Py_DECREF(seq);
    if (PyErr_Occurred()) {
        return -1;
    }
    return size;
}

#define new_ref(obj) (Py_INCREF(obj), obj)

PyObject * empty_tuple;

PyTypeObject * Context_type;
PyTypeObject * Buffer_type;
PyTypeObject * Listener_type;
PyTypeObject * Source_type;

struct BaseObject {
    PyObject_HEAD
    BaseObject * prev;
    BaseObject * next;
};

struct Context : public BaseObject {
    ALCdevice * device;
    ALCcontext * ctx;
    void * libal;

    struct Listener * listener;

    struct {
        PyObject * format_mono8;
        PyObject * format_mono16;
        PyObject * format_stereo8;
        PyObject * format_stereo16;
        PyObject * inverse_distance;
        PyObject * inverse_distance_clamped;
        PyObject * linear_distance;
        PyObject * linear_distance_clamped;
        PyObject * exponent_distance;
        PyObject * exponent_distance_clamped;
    } consts;

    struct {
        LPALCOPENDEVICE OpenDevice;
        LPALCCREATECONTEXT CreateContext;
        LPALCMAKECONTEXTCURRENT MakeContextCurrent;
        LPALCGETERROR GetError;
    } alc;

    struct {
        LPALENABLE Enable;
        LPALDISABLE Disable;
        LPALISENABLED IsEnabled;
        LPALGETSTRING GetString;
        LPALGETBOOLEANV GetBooleanv;
        LPALGETINTEGERV GetIntegerv;
        LPALGETFLOATV GetFloatv;
        LPALGETDOUBLEV GetDoublev;
        LPALGETBOOLEAN GetBoolean;
        LPALGETINTEGER GetInteger;
        LPALGETFLOAT GetFloat;
        LPALGETDOUBLE GetDouble;
        LPALGETERROR GetError;
        LPALISEXTENSIONPRESENT IsExtensionPresent;
        LPALGETPROCADDRESS GetProcAddress;
        LPALGETENUMVALUE GetEnumValue;
        LPALLISTENERF Listenerf;
        LPALLISTENER3F Listener3f;
        LPALLISTENERFV Listenerfv;
        LPALLISTENERI Listeneri;
        LPALLISTENER3I Listener3i;
        LPALLISTENERIV Listeneriv;
        LPALGETLISTENERF GetListenerf;
        LPALGETLISTENER3F GetListener3f;
        LPALGETLISTENERFV GetListenerfv;
        LPALGETLISTENERI GetListeneri;
        LPALGETLISTENER3I GetListener3i;
        LPALGETLISTENERIV GetListeneriv;
        LPALGENSOURCES GenSources;
        LPALDELETESOURCES DeleteSources;
        LPALISSOURCE IsSource;
        LPALSOURCEF Sourcef;
        LPALSOURCE3F Source3f;
        LPALSOURCEFV Sourcefv;
        LPALSOURCEI Sourcei;
        LPALSOURCE3I Source3i;
        LPALSOURCEIV Sourceiv;
        LPALGETSOURCEF GetSourcef;
        LPALGETSOURCE3F GetSource3f;
        LPALGETSOURCEFV GetSourcefv;
        LPALGETSOURCEI GetSourcei;
        LPALGETSOURCE3I GetSource3i;
        LPALGETSOURCEIV GetSourceiv;
        LPALSOURCEPLAYV SourcePlayv;
        LPALSOURCESTOPV SourceStopv;
        LPALSOURCEREWINDV SourceRewindv;
        LPALSOURCEPAUSEV SourcePausev;
        LPALSOURCEPLAY SourcePlay;
        LPALSOURCESTOP SourceStop;
        LPALSOURCEREWIND SourceRewind;
        LPALSOURCEPAUSE SourcePause;
        LPALSOURCEQUEUEBUFFERS SourceQueueBuffers;
        LPALSOURCEUNQUEUEBUFFERS SourceUnqueueBuffers;
        LPALGENBUFFERS GenBuffers;
        LPALDELETEBUFFERS DeleteBuffers;
        LPALISBUFFER IsBuffer;
        LPALBUFFERDATA BufferData;
        LPALBUFFERF Bufferf;
        LPALBUFFER3F Buffer3f;
        LPALBUFFERFV Bufferfv;
        LPALBUFFERI Bufferi;
        LPALBUFFER3I Buffer3i;
        LPALBUFFERIV Bufferiv;
        LPALGETBUFFERF GetBufferf;
        LPALGETBUFFER3F GetBuffer3f;
        LPALGETBUFFERFV GetBufferfv;
        LPALGETBUFFERI GetBufferi;
        LPALGETBUFFER3I GetBuffer3i;
        LPALGETBUFFERIV GetBufferiv;
        LPALDOPPLERFACTOR DopplerFactor;
        LPALDOPPLERVELOCITY DopplerVelocity;
        LPALSPEEDOFSOUND SpeedOfSound;
        LPALDISTANCEMODEL DistanceModel;
    } al;
};

struct Buffer : public BaseObject {
    struct Context * ctx;
    int alo;
    int format;
    int frequency;
    int size;
    int bound;
};

struct Listener : public BaseObject {
    struct Context * ctx;
};

struct Source : public BaseObject {
    struct Context * ctx;
    struct Buffer * buffer;
    int alo;
    bool playing;
};

void BaseObject_dealloc(BaseObject * self) {
    Py_TYPE(self)->tp_free(self);
}

Buffer * Context_meth_buffer(Context * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"data", "format", "frequency", NULL};

    PyObject * data = NULL;
    int format = AL_FORMAT_MONO16;
    int frequency = 44100;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|Oii", keywords, &data, &format, &frequency)) {
        return NULL;
    }

    if (!PyArg_ParseTuple(args, "|O", &data)) {
        return NULL;
    }

    Buffer * res = PyObject_New(Buffer, Buffer_type);
    res->prev = self;
    res->next = self->next;
    self->next = res;
    res->ctx = self;

    res->format = format;
    res->frequency = frequency;
    res->size = 0;
    res->bound = 0;

    self->al.GenBuffers(1, (ALuint *)&res->alo);
    if (data) {
        PyObject * call = PyObject_CallMethod((PyObject *)res, "write", "Oii", data, format, frequency);
        Py_XDECREF(call);
        if (!call) {
            return NULL;
        }
    }
    return res;
}

PyObject * Buffer_meth_write(Buffer * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"data", "format", "frequency", NULL};

    Py_buffer view = {};
    int format = self->format;
    int frequency = self->frequency;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "y*|ii", keywords, &view, &format, &frequency)) {
        return NULL;
    }

    if (self->bound != 0) {
        PyErr_BadInternalCall();
        return NULL;
    }

    self->format = format;
    self->frequency = frequency;
    self->size = (int)view.len;

    self->ctx->al.BufferData(self->alo, self->format, view.buf, self->size, self->frequency);
    Py_RETURN_NONE;
}

PyMethodDef Buffer_methods[] = {
    {"write", (PyCFunction)Buffer_meth_write, METH_VARARGS | METH_KEYWORDS, NULL},
    {},
};

PyMemberDef Buffer_members[] = {
    {"format", T_INT, offsetof(Buffer, format), READONLY, NULL},
    {"frequency", T_INT, offsetof(Buffer, frequency), READONLY, NULL},
    {"size", T_INT, offsetof(Buffer, size), READONLY, NULL},
    {"alo", T_INT, offsetof(Buffer, alo), READONLY, NULL},
    {},
};

PyType_Slot Buffer_slots[] = {
    {Py_tp_methods, Buffer_methods},
    {Py_tp_members, Buffer_members},
    {Py_tp_dealloc, (void *)BaseObject_dealloc},
    {},
};

PyObject * Listener_meth_change(Listener * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {
        "gain",
        "position",
        "velocity",
        "orientation",
        NULL,
    };

    PyObject * gain = Py_None;
    PyObject * position = Py_None;
    PyObject * velocity = Py_None;
    PyObject * orientation = Py_None;

    int args_ok = PyArg_ParseTupleAndKeywords(
        args,
        kwargs,
        "|OOOO",
        keywords,
        &gain,
        &position,
        &velocity,
        &orientation
    );

    if (!args_ok) {
        return NULL;
    }

    if (gain != Py_None) {
        self->ctx->al.Listenerf(AL_GAIN, (float)PyFloat_AsDouble(gain));
    }
    if (position != Py_None) {
        float value[3] = {};
        py_floats(value, 3, 3, position);
        self->ctx->al.Listenerfv(AL_POSITION, value);
    }
    if (velocity != Py_None) {
        float value[3] = {};
        py_floats(value, 3, 3, velocity);
        self->ctx->al.Listenerfv(AL_VELOCITY, value);
    }
    if (orientation != Py_None) {
        float value[6] = {};
        py_floats(value, 6, 6, orientation);
        self->ctx->al.Listenerfv(AL_ORIENTATION, value);
    }
    Py_RETURN_NONE;
}

PyType_Spec Buffer_spec = {"modernal.Buffer", sizeof(Buffer), 0, Py_TPFLAGS_DEFAULT, Buffer_slots};

PyMethodDef Listener_methods[] = {
    {"change", (PyCFunction)Listener_meth_change, METH_VARARGS | METH_KEYWORDS, NULL},
    {},
};

PyType_Slot Listener_slots[] = {
    {Py_tp_methods, Listener_methods},
    {Py_tp_dealloc, (void *)BaseObject_dealloc},
    {},
};

PyType_Spec Listener_spec = {"modernal.Listener", sizeof(Listener), 0, Py_TPFLAGS_DEFAULT, Listener_slots};

Source * Context_meth_source(Context * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"buffer", NULL};

    PyObject * buffer = Py_None;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|O!", keywords, Buffer_type, &buffer)) {
        return NULL;
    }

    Source * res = PyObject_New(Source, Source_type);
    res->prev = self;
    res->next = self->next;
    self->next = res;
    res->ctx = self;

    res->buffer = NULL;
    res->playing = false;

    self->al.GenSources(1, (ALuint *)&res->alo);

    if (PyObject_SetAttrString((PyObject *)res, "buffer", buffer) < 0) {
        return NULL;
    }

    return res;
}

PyObject * Source_meth_change(Source * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {
        "loop",
        "gain",
        "pitch",
        "time",
        "min_gain",
        "max_gain",
        "max_distance",
        "rolloff_factor",
        "cone_outer_gain",
        "cone_inner_angle",
        "cone_outer_angle",
        "reference_dinstance",
        "position",
        "velocity",
        "direction",
        NULL,
    };

    PyObject * loop = Py_None;
    PyObject * gain = Py_None;
    PyObject * pitch = Py_None;
    PyObject * time = Py_None;
    PyObject * min_gain = Py_None;
    PyObject * max_gain = Py_None;
    PyObject * max_distance = Py_None;
    PyObject * rolloff_factor = Py_None;
    PyObject * cone_outer_gain = Py_None;
    PyObject * cone_inner_angle = Py_None;
    PyObject * cone_outer_angle = Py_None;
    PyObject * reference_dinstance = Py_None;
    PyObject * position = Py_None;
    PyObject * velocity = Py_None;
    PyObject * direction = Py_None;

    int args_ok = PyArg_ParseTupleAndKeywords(
        args,
        kwargs,
        "|OOOOOOOOOOOOOOO",
        keywords,
        &loop,
        &gain,
        &pitch,
        &time,
        &min_gain,
        &max_gain,
        &max_distance,
        &rolloff_factor,
        &cone_outer_gain,
        &cone_inner_angle,
        &cone_outer_angle,
        &reference_dinstance,
        &position,
        &velocity,
        &direction
    );

    if (!args_ok) {
        return NULL;
    }

    if (loop != Py_None) {
        self->ctx->al.Sourcei(self->alo, AL_LOOPING, PyObject_IsTrue(loop));
    }
    if (gain != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_GAIN, (float)PyFloat_AsDouble(gain));
    }
    if (pitch != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_PITCH, (float)PyFloat_AsDouble(pitch));
    }
    if (time != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_SEC_OFFSET, (float)PyFloat_AsDouble(time));
    }
    if (min_gain != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_MIN_GAIN, (float)PyFloat_AsDouble(min_gain));
    }
    if (max_gain != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_MAX_GAIN, (float)PyFloat_AsDouble(max_gain));
    }
    if (max_distance != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_MAX_DISTANCE, (float)PyFloat_AsDouble(max_distance));
    }
    if (rolloff_factor != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_ROLLOFF_FACTOR, (float)PyFloat_AsDouble(rolloff_factor));
    }
    if (cone_outer_gain != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_CONE_OUTER_GAIN, (float)PyFloat_AsDouble(cone_outer_gain));
    }
    if (cone_inner_angle != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_CONE_INNER_ANGLE, (float)PyFloat_AsDouble(cone_inner_angle));
    }
    if (cone_outer_angle != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_CONE_OUTER_ANGLE, (float)PyFloat_AsDouble(cone_outer_angle));
    }
    if (reference_dinstance != Py_None) {
        self->ctx->al.Sourcef(self->alo, AL_REFERENCE_DISTANCE, (float)PyFloat_AsDouble(reference_dinstance));
    }
    if (position != Py_None) {
        float value[3] = {};
        py_floats(value, 3, 3, position);
        self->ctx->al.Sourcefv(self->alo, AL_POSITION, value);
    }
    if (velocity != Py_None) {
        float value[3] = {};
        py_floats(value, 3, 3, velocity);
        self->ctx->al.Sourcefv(self->alo, AL_VELOCITY, value);
    }
    if (direction != Py_None) {
        float value[3] = {};
        py_floats(value, 3, 3, direction);
        self->ctx->al.Sourcefv(self->alo, AL_DIRECTION, value);
    }

    Py_RETURN_NONE;
}

PyObject * Source_meth_play(Source * self, PyObject * args, PyObject * kwargs) {
    Buffer * buffer = NULL;

    if (!PyArg_ParseTuple(args, "|O!", Buffer_type, &buffer)) {
        return NULL;
    }

    if (self->playing) {
        PyObject * call = PyObject_CallMethod((PyObject *)self, "stop", NULL);
        Py_XDECREF(call);
        if (!call) {
            return NULL;
        }
    }
    PyObject * call = Source_meth_change(self, empty_tuple, kwargs);
    Py_XDECREF(call);
    if (!call) {
        return NULL;
    }
    if (buffer) {
        if (PyObject_SetAttrString((PyObject *)self, "buffer", (PyObject *)buffer) < 0) {
            return NULL;
        }
    }
    self->buffer->bound += 1;
    self->ctx->al.Sourcei(self->alo, AL_BUFFER, self->buffer->alo);
    self->ctx->al.SourcePlay(self->alo);
    self->playing = true;
    Py_RETURN_NONE;
}

PyObject * Source_meth_stop(Source * self) {
    if (self->playing) {
        self->ctx->al.SourceStop(self->alo);
        self->ctx->al.Sourcei(self->alo, AL_BUFFER, 0);
        self->buffer->bound -= 1;
    }
    Py_RETURN_NONE;
}

PyObject * Source_meth_time(Source * self) {
    float time = 0.0f;
    self->ctx->al.GetSourcefv(self->alo, AL_SEC_OFFSET, &time);
    return PyFloat_FromDouble(time);
}

PyObject * Source_get_buffer(Source * self) {
    if (self->buffer) {
        return (PyObject *)new_ref(self->buffer);
    }
    Py_RETURN_NONE;
}

int Source_set_buffer(Source * self, PyObject * value) {
    if (self->playing) {
        PyErr_BadInternalCall();
        return -1;
    }
    if (value == Py_None) {
        self->buffer = NULL;
        return 0;
    }
    if (Py_TYPE(value) != Buffer_type) {
        PyErr_BadInternalCall();
        return -1;
    }
    Buffer * buffer = (Buffer *)value;
    self->buffer = new_ref(buffer);
    return 0;
}

PyMethodDef Source_methods[] = {
    {"change", (PyCFunction)Source_meth_change, METH_VARARGS | METH_KEYWORDS, NULL},
    {"play", (PyCFunction)Source_meth_play, METH_VARARGS | METH_KEYWORDS, NULL},
    {"stop", (PyCFunction)Source_meth_stop, METH_NOARGS, NULL},
    {"time", (PyCFunction)Source_meth_time, METH_NOARGS, NULL},
    {},
};

PyGetSetDef Source_getset[] = {
    {"buffer", (getter)Source_get_buffer, (setter)Source_set_buffer, NULL, NULL},
    {},
};

PyMemberDef Source_members[] = {
    {"alo", T_INT, offsetof(Source, alo), READONLY, NULL},
    {},
};

PyType_Slot Source_slots[] = {
    {Py_tp_methods, Source_methods},
    {Py_tp_getset, Source_getset},
    {Py_tp_members, Source_members},
    {Py_tp_dealloc, (void *)BaseObject_dealloc},
    {},
};

PyType_Spec Source_spec = {"modernal.Source", sizeof(Source), 0, Py_TPFLAGS_DEFAULT, Source_slots};

Context * modernal_meth_create_context(PyObject * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"device_name", "libal", NULL};

    const char * device_name = NULL;
    const char * libal = DEFAULT_LIBAL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|ss", keywords, &device_name, &libal)) {
        return NULL;
    }

    Context * res = PyObject_New(Context, Context_type);
    res->next = res;
    res->prev = res;

    res->libal = load_al_library(libal);
    if (!res->libal) {
        PyErr_Format(PyExc_Exception, "%s not loaded", libal);
        return NULL;
    }

    #define load(name) *(void **)&res->alc.name = (void *)load_al_method(res->libal, "alc" # name)
    load(OpenDevice);
    load(CreateContext);
    load(MakeContextCurrent);
    load(GetError);
    #undef load

    if (PyErr_Occurred()) {
        return NULL;
    }

    res->device = res->alc.OpenDevice(device_name);
    if (!res->device) {
        return NULL;
    }

    int attribs[] = {
        0, 0,
    };

    res->ctx = res->alc.CreateContext(res->device, attribs);
    if (!res->ctx) {
        return NULL;
    }

    if (!res->alc.MakeContextCurrent(res->ctx)) {
        return NULL;
    }

    #define load(name) *(void **)&res->al.name = (void *)load_al_method(res->libal, "al" # name)
    load(Enable);
    load(Disable);
    load(IsEnabled);
    load(GetString);
    load(GetBooleanv);
    load(GetIntegerv);
    load(GetFloatv);
    load(GetDoublev);
    load(GetBoolean);
    load(GetInteger);
    load(GetFloat);
    load(GetDouble);
    load(GetError);
    load(IsExtensionPresent);
    load(GetProcAddress);
    load(GetEnumValue);
    load(Listenerf);
    load(Listener3f);
    load(Listenerfv);
    load(Listeneri);
    load(Listener3i);
    load(Listeneriv);
    load(GetListenerf);
    load(GetListener3f);
    load(GetListenerfv);
    load(GetListeneri);
    load(GetListener3i);
    load(GetListeneriv);
    load(GenSources);
    load(DeleteSources);
    load(IsSource);
    load(Sourcef);
    load(Source3f);
    load(Sourcefv);
    load(Sourcei);
    load(Source3i);
    load(Sourceiv);
    load(GetSourcef);
    load(GetSource3f);
    load(GetSourcefv);
    load(GetSourcei);
    load(GetSource3i);
    load(GetSourceiv);
    load(SourcePlayv);
    load(SourceStopv);
    load(SourceRewindv);
    load(SourcePausev);
    load(SourcePlay);
    load(SourceStop);
    load(SourceRewind);
    load(SourcePause);
    load(SourceQueueBuffers);
    load(SourceUnqueueBuffers);
    load(GenBuffers);
    load(DeleteBuffers);
    load(IsBuffer);
    load(BufferData);
    load(Bufferf);
    load(Buffer3f);
    load(Bufferfv);
    load(Bufferi);
    load(Buffer3i);
    load(Bufferiv);
    load(GetBufferf);
    load(GetBuffer3f);
    load(GetBufferfv);
    load(GetBufferi);
    load(GetBuffer3i);
    load(GetBufferiv);
    load(DopplerFactor);
    load(DopplerVelocity);
    load(SpeedOfSound);
    load(DistanceModel);
    #undef load

    if (PyErr_Occurred()) {
        return NULL;
    }

    res->listener = PyObject_New(Listener, Listener_type);

    res->consts.format_mono8 = PyLong_FromLong(AL_FORMAT_MONO8);
    res->consts.format_mono16 = PyLong_FromLong(AL_FORMAT_MONO16);
    res->consts.format_stereo8 = PyLong_FromLong(AL_FORMAT_STEREO8);
    res->consts.format_stereo16 = PyLong_FromLong(AL_FORMAT_STEREO16);
    res->consts.inverse_distance = PyLong_FromLong(AL_INVERSE_DISTANCE);
    res->consts.inverse_distance_clamped = PyLong_FromLong(AL_INVERSE_DISTANCE_CLAMPED);
    res->consts.linear_distance = PyLong_FromLong(AL_LINEAR_DISTANCE);
    res->consts.linear_distance_clamped = PyLong_FromLong(AL_LINEAR_DISTANCE_CLAMPED);
    res->consts.exponent_distance = PyLong_FromLong(AL_EXPONENT_DISTANCE);
    res->consts.exponent_distance_clamped = PyLong_FromLong(AL_EXPONENT_DISTANCE_CLAMPED);

    return res;
}

PyObject * Context_meth_objects(Context * self) {
    PyObject * res = PyList_New(0);
    BaseObject * obj = self->next;
    while (obj != self) {
        PyList_Append(res, (PyObject *)obj);
    }
    return res;
}

PyObject * Context_meth_release(Context * self, BaseObject * obj) {
    obj->next->prev = obj->prev;
    obj->prev->next = obj->next;
    Py_DECREF(obj);
    Py_RETURN_NONE;
}

PyMethodDef Context_methods[] = {
    {"buffer", (PyCFunction)Context_meth_buffer, METH_VARARGS | METH_KEYWORDS, NULL},
    {"source", (PyCFunction)Context_meth_source, METH_VARARGS | METH_KEYWORDS, NULL},
    {"objects", (PyCFunction)Context_meth_objects, METH_NOARGS, NULL},
    {"release", (PyCFunction)Context_meth_release, METH_O, NULL},
    {},
};

PyMemberDef Context_members[] = {
    {"listener", T_OBJECT, offsetof(Context, listener), READONLY, NULL},

    {"FORMAT_MONO8", T_OBJECT, offsetof(Context, consts.format_mono8), READONLY, NULL},
    {"FORMAT_MONO16", T_OBJECT, offsetof(Context, consts.format_mono16), READONLY, NULL},
    {"FORMAT_STEREO8", T_OBJECT, offsetof(Context, consts.format_stereo8), READONLY, NULL},
    {"FORMAT_STEREO16", T_OBJECT, offsetof(Context, consts.format_stereo16), READONLY, NULL},
    {"INVERSE_DISTANCE", T_OBJECT, offsetof(Context, consts.inverse_distance), READONLY, NULL},
    {"INVERSE_DISTANCE_CLAMPED", T_OBJECT, offsetof(Context, consts.inverse_distance_clamped), READONLY, NULL},
    {"LINEAR_DISTANCE", T_OBJECT, offsetof(Context, consts.linear_distance), READONLY, NULL},
    {"LINEAR_DISTANCE_CLAMPED", T_OBJECT, offsetof(Context, consts.linear_distance_clamped), READONLY, NULL},
    {"EXPONENT_DISTANCE", T_OBJECT, offsetof(Context, consts.exponent_distance), READONLY, NULL},
    {"EXPONENT_DISTANCE_CLAMPED", T_OBJECT, offsetof(Context, consts.exponent_distance_clamped), READONLY, NULL},
    {},
};

PyType_Slot Context_slots[] = {
    {Py_tp_methods, Context_methods},
    {Py_tp_members, Context_members},
    {Py_tp_dealloc, (void *)BaseObject_dealloc},
    {},
};

PyType_Spec Context_spec = {"modernal.Context", sizeof(Context), 0, Py_TPFLAGS_DEFAULT, Context_slots};

PyMethodDef module_methods[] = {
    {"create_context", (PyCFunction)modernal_meth_create_context, METH_VARARGS | METH_KEYWORDS, NULL},
    {},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "modernal", NULL, -1, module_methods};

extern "C" PyObject * PyInit_modernal() {
    PyObject * module = PyModule_Create(&module_def);

    empty_tuple = PyTuple_New(0);

    Context_type = (PyTypeObject *)PyType_FromSpec(&Context_spec);
    Buffer_type = (PyTypeObject *)PyType_FromSpec(&Buffer_spec);
    Listener_type = (PyTypeObject *)PyType_FromSpec(&Listener_spec);
    Source_type = (PyTypeObject *)PyType_FromSpec(&Source_spec);

    PyModule_AddObject(module, "Context", (PyObject *)Context_type);
    PyModule_AddObject(module, "Buffer", (PyObject *)Buffer_type);
    PyModule_AddObject(module, "Listener", (PyObject *)Listener_type);
    PyModule_AddObject(module, "Source", (PyObject *)Source_type);

    return module;
}
