#ifndef SCHEMA_READER_H
#define SCHEMA_READER_H

/* Generated by flatcc 0.6.2 FlatBuffers schema compiler for C by dvide.com */

#ifndef FLATBUFFERS_COMMON_READER_H
    #include "flatbuffers_common_reader.h"
#endif
#include "flatcc/flatcc_flatbuffers.h"
#ifndef __alignas_is_defined
    #include <stdalign.h>
#endif
#include "flatcc/flatcc_prologue.h"
#ifndef flatbuffers_identifier
    #define flatbuffers_identifier 0
#endif
#ifndef flatbuffers_extension
    #define flatbuffers_extension "bin"
#endif

typedef struct Comms_Version Comms_Version_t;
typedef const Comms_Version_t* Comms_Version_struct_t;
typedef Comms_Version_t* Comms_Version_mutable_struct_t;
typedef const Comms_Version_t* Comms_Version_vec_t;
typedef Comms_Version_t* Comms_Version_mutable_vec_t;

typedef const struct Comms_Command_table* Comms_Command_table_t;
typedef struct Comms_Command_table* Comms_Command_mutable_table_t;
typedef const flatbuffers_uoffset_t* Comms_Command_vec_t;
typedef flatbuffers_uoffset_t* Comms_Command_mutable_vec_t;
#ifndef Comms_Version_file_identifier
    #define Comms_Version_file_identifier 0
#endif
/* deprecated, use Comms_Version_file_identifier */
#ifndef Comms_Version_identifier
    #define Comms_Version_identifier 0
#endif
#define Comms_Version_type_hash       ((flatbuffers_thash_t) 0x4331ab2c)
#define Comms_Version_type_identifier "\x2c\xab\x31\x43"
#ifndef Comms_Version_file_extension
    #define Comms_Version_file_extension "bin"
#endif
#ifndef Comms_Command_file_identifier
    #define Comms_Command_file_identifier 0
#endif
/* deprecated, use Comms_Command_file_identifier */
#ifndef Comms_Command_identifier
    #define Comms_Command_identifier 0
#endif
#define Comms_Command_type_hash       ((flatbuffers_thash_t) 0x78d7e429)
#define Comms_Command_type_identifier "\x29\xe4\xd7\x78"
#ifndef Comms_Command_file_extension
    #define Comms_Command_file_extension "bin"
#endif

typedef int8_t Comms_CommandID_enum_t;
__flatbuffers_define_integer_type(Comms_CommandID, Comms_CommandID_enum_t, 8)
#define Comms_CommandID_OPEN  ((Comms_CommandID_enum_t) INT8_C(0))
#define Comms_CommandID_CLOSE ((Comms_CommandID_enum_t) INT8_C(1))
#define Comms_CommandID_SET   ((Comms_CommandID_enum_t) INT8_C(2))
#define Comms_CommandID_GET   ((Comms_CommandID_enum_t) INT8_C(3))
#define Comms_CommandID_RET   ((Comms_CommandID_enum_t) INT8_C(4))
#define Comms_CommandID_ERR   ((Comms_CommandID_enum_t) INT8_C(5))
#define Comms_CommandID_RES   ((Comms_CommandID_enum_t) INT8_C(6))
#define Comms_CommandID_SAVE  ((Comms_CommandID_enum_t) INT8_C(7))

    static inline const char* Comms_CommandID_name(Comms_CommandID_enum_t value)
{
    switch (value)
    {
    case Comms_CommandID_OPEN:
        return "OPEN";
    case Comms_CommandID_CLOSE:
        return "CLOSE";
    case Comms_CommandID_SET:
        return "SET";
    case Comms_CommandID_GET:
        return "GET";
    case Comms_CommandID_RET:
        return "RET";
    case Comms_CommandID_ERR:
        return "ERR";
    case Comms_CommandID_RES:
        return "RES";
    case Comms_CommandID_SAVE:
        return "SAVE";
    default:
        return "";
    }
}

static inline int Comms_CommandID_is_known_value(Comms_CommandID_enum_t value)
{
    switch (value)
    {
    case Comms_CommandID_OPEN:
        return 1;
    case Comms_CommandID_CLOSE:
        return 1;
    case Comms_CommandID_SET:
        return 1;
    case Comms_CommandID_GET:
        return 1;
    case Comms_CommandID_RET:
        return 1;
    case Comms_CommandID_ERR:
        return 1;
    case Comms_CommandID_RES:
        return 1;
    case Comms_CommandID_SAVE:
        return 1;
    default:
        return 0;
    }
}

typedef int8_t Comms_VariableID_enum_t;
__flatbuffers_define_integer_type(Comms_VariableID, Comms_VariableID_enum_t, 8)
#define Comms_VariableID_config_name    ((Comms_VariableID_enum_t) INT8_C(0))
#define Comms_VariableID_config_version ((Comms_VariableID_enum_t) INT8_C(1))
#define Comms_VariableID_config_last_revision_date \
    ((Comms_VariableID_enum_t) INT8_C(2))
#define Comms_VariableID_torque_map    ((Comms_VariableID_enum_t) INT8_C(3))
#define Comms_VariableID_inverter_mode ((Comms_VariableID_enum_t) INT8_C(4))
#define Comms_VariableID_disable_torque_requests \
    ((Comms_VariableID_enum_t) INT8_C(5))
#define Comms_VariableID_apps_1_adc_min ((Comms_VariableID_enum_t) INT8_C(6))
#define Comms_VariableID_apps_1_adc_max ((Comms_VariableID_enum_t) INT8_C(7))
#define Comms_VariableID_apps_2_adc_min ((Comms_VariableID_enum_t) INT8_C(8))
#define Comms_VariableID_apps_2_adc_max ((Comms_VariableID_enum_t) INT8_C(9))
#define Comms_VariableID_bps_adc_min    ((Comms_VariableID_enum_t) INT8_C(10))
#define Comms_VariableID_bps_adc_max    ((Comms_VariableID_enum_t) INT8_C(11))
#define Comms_VariableID_bps_fully_pressed_threshold \
    ((Comms_VariableID_enum_t) INT8_C(12))
#define Comms_VariableID_enable_lapsim_testbench \
    ((Comms_VariableID_enum_t) INT8_C(13))
#define Comms_VariableID_lapsim_testbench_laps \
    ((Comms_VariableID_enum_t) INT8_C(14))

    static inline const
    char* Comms_VariableID_name(Comms_VariableID_enum_t value)
{
    switch (value)
    {
    case Comms_VariableID_config_name:
        return "config_name";
    case Comms_VariableID_config_version:
        return "config_version";
    case Comms_VariableID_config_last_revision_date:
        return "config_last_revision_date";
    case Comms_VariableID_torque_map:
        return "torque_map";
    case Comms_VariableID_inverter_mode:
        return "inverter_mode";
    case Comms_VariableID_disable_torque_requests:
        return "disable_torque_requests";
    case Comms_VariableID_apps_1_adc_min:
        return "apps_1_adc_min";
    case Comms_VariableID_apps_1_adc_max:
        return "apps_1_adc_max";
    case Comms_VariableID_apps_2_adc_min:
        return "apps_2_adc_min";
    case Comms_VariableID_apps_2_adc_max:
        return "apps_2_adc_max";
    case Comms_VariableID_bps_adc_min:
        return "bps_adc_min";
    case Comms_VariableID_bps_adc_max:
        return "bps_adc_max";
    case Comms_VariableID_bps_fully_pressed_threshold:
        return "bps_fully_pressed_threshold";
    case Comms_VariableID_enable_lapsim_testbench:
        return "enable_lapsim_testbench";
    case Comms_VariableID_lapsim_testbench_laps:
        return "lapsim_testbench_laps";
    default:
        return "";
    }
}

static inline int Comms_VariableID_is_known_value(Comms_VariableID_enum_t value)
{
    switch (value)
    {
    case Comms_VariableID_config_name:
        return 1;
    case Comms_VariableID_config_version:
        return 1;
    case Comms_VariableID_config_last_revision_date:
        return 1;
    case Comms_VariableID_torque_map:
        return 1;
    case Comms_VariableID_inverter_mode:
        return 1;
    case Comms_VariableID_disable_torque_requests:
        return 1;
    case Comms_VariableID_apps_1_adc_min:
        return 1;
    case Comms_VariableID_apps_1_adc_max:
        return 1;
    case Comms_VariableID_apps_2_adc_min:
        return 1;
    case Comms_VariableID_apps_2_adc_max:
        return 1;
    case Comms_VariableID_bps_adc_min:
        return 1;
    case Comms_VariableID_bps_adc_max:
        return 1;
    case Comms_VariableID_bps_fully_pressed_threshold:
        return 1;
    case Comms_VariableID_enable_lapsim_testbench:
        return 1;
    case Comms_VariableID_lapsim_testbench_laps:
        return 1;
    default:
        return 0;
    }
}

struct Comms_Version
{
    alignas(1) int8_t a;
    alignas(1) int8_t b;
    alignas(1) int8_t c;
};
static_assert(sizeof(Comms_Version_t) == 3, "struct size mismatch");

static inline const Comms_Version_t*
Comms_Version__const_ptr_add(const Comms_Version_t* p, size_t i)
{
    return p + i;
}
static inline Comms_Version_t* Comms_Version__ptr_add(Comms_Version_t* p,
                                                      size_t i)
{
    return p + i;
}
static inline Comms_Version_struct_t
Comms_Version_vec_at(Comms_Version_vec_t vec, size_t i)
    __flatbuffers_struct_vec_at(vec, i) static inline size_t
    Comms_Version__size(void)
{
    return 3;
}
static inline size_t Comms_Version_vec_len(Comms_Version_vec_t vec)
    __flatbuffers_vec_len(vec) __flatbuffers_struct_as_root(Comms_Version)

        __flatbuffers_define_struct_scalar_field(Comms_Version,
                                                 a,
                                                 flatbuffers_int8,
                                                 int8_t)
            __flatbuffers_define_struct_scalar_field(Comms_Version,
                                                     b,
                                                     flatbuffers_int8,
                                                     int8_t)
                __flatbuffers_define_struct_scalar_field(Comms_Version,
                                                         c,
                                                         flatbuffers_int8,
                                                         int8_t)

                    struct Comms_Command_table
{
    uint8_t unused__;
};

static inline size_t Comms_Command_vec_len(Comms_Command_vec_t vec)
    __flatbuffers_vec_len(vec) static inline Comms_Command_table_t
    Comms_Command_vec_at(Comms_Command_vec_t vec, size_t i)
        __flatbuffers_offset_vec_at(Comms_Command_table_t, vec, i, 0)
            __flatbuffers_table_as_root(Comms_Command)

                __flatbuffers_define_scalar_field(0,
                                                  Comms_Command,
                                                  id,
                                                  Comms_CommandID,
                                                  Comms_CommandID_enum_t,
                                                  INT8_C(0))
                    __flatbuffers_define_scalar_field(1,
                                                      Comms_Command,
                                                      var,
                                                      Comms_VariableID,
                                                      Comms_VariableID_enum_t,
                                                      INT8_C(0))
                        __flatbuffers_define_scalar_field(2,
                                                          Comms_Command,
                                                          val,
                                                          flatbuffers_int32,
                                                          int32_t,
                                                          INT32_C(0))
                            __flatbuffers_define_string_field(3,
                                                              Comms_Command,
                                                              config_name,
                                                              0)
                                __flatbuffers_define_struct_field(
                                    4,
                                    Comms_Command,
                                    config_version,
                                    Comms_Version_struct_t,
                                    0)

#include "flatcc/flatcc_epilogue.h"
#endif /* SCHEMA_READER_H */
