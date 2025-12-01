
/* Generated code - do not edit by hand.

This includes all the CLAP API typedefs and structs, but:
	* renamed clap_ -> wclap_
	* T * replaced by Pointer<T>
	* function pointers replaced by Function<Return, Args...>

You should be able to include this inside another namespace, as long as Function<> and Pointer<> are defined.  These must be simple wrappers around integers, and have the same size as pointers inside the WASM module.
*/

//---------- version.h

typedef struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
} wclap_version;
static const WCLAP_CONSTEXPR wclap_version WCLAP_VERSION = WCLAP_VERSION_INIT;
WCLAP_NODISCARD static inline WCLAP_CONSTEXPR bool
wclap_version_is_compatible(const wclap_version v) {
   return v.major >= 1;
}

//---------- entry.h

typedef struct wclap_plugin_entry {
   wclap_version wclap_version;
   Function<bool, Pointer<const char>> init;
   Function<void> deinit;
   Function<Pointer<const void>, Pointer<const char>> get_factory;
} wclap_plugin_entry;
WCLAP_EXPORT extern const wclap_plugin_entry wclap_entry;

//---------- host.h

typedef struct wclap_host {
   wclap_version wclap_version;
   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void>, Pointer<const struct wclap_host>, Pointer<const char>> get_extension;
   Function<void, Pointer<const struct wclap_host>> request_restart;
   Function<void, Pointer<const struct wclap_host>> request_process;
   Function<void, Pointer<const struct wclap_host>> request_callback;
} wclap_host;

//---------- fixedpoint.h

static const WCLAP_CONSTEXPR int64_t WCLAP_BEATTIME_FACTOR = 1LL << 31;
static const WCLAP_CONSTEXPR int64_t WCLAP_SECTIME_FACTOR = 1LL << 31;
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;

//---------- id.h

typedef uint32_t wclap_id;
static const WCLAP_CONSTEXPR wclap_id WCLAP_INVALID_ID = UINT32_MAX;

//---------- events.h

typedef struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
} wclap_event_header;
static const WCLAP_CONSTEXPR uint16_t WCLAP_CORE_EVENT_SPACE_ID = 0;
enum wclap_event_flags {
   WCLAP_EVENT_IS_LIVE = 1 << 0,
   WCLAP_EVENT_DONT_RECORD = 1 << 1,
};
enum {
   WCLAP_EVENT_NOTE_ON = 0,
   WCLAP_EVENT_NOTE_OFF = 1,
   WCLAP_EVENT_NOTE_CHOKE = 2,
   WCLAP_EVENT_NOTE_END = 3,
   WCLAP_EVENT_NOTE_EXPRESSION = 4,
   WCLAP_EVENT_PARAM_VALUE = 5,
   WCLAP_EVENT_PARAM_MOD = 6,
   WCLAP_EVENT_PARAM_GESTURE_BEGIN = 7,
   WCLAP_EVENT_PARAM_GESTURE_END = 8,
   WCLAP_EVENT_TRANSPORT = 9,
   WCLAP_EVENT_MIDI = 10,
   WCLAP_EVENT_MIDI_SYSEX = 11,
   WCLAP_EVENT_MIDI2 = 12,
};
typedef struct wclap_event_note {
   wclap_event_header header;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double velocity;
} wclap_event_note;
enum {
   WCLAP_NOTE_EXPRESSION_VOLUME = 0,
   WCLAP_NOTE_EXPRESSION_PAN = 1,
   WCLAP_NOTE_EXPRESSION_TUNING = 2,
   WCLAP_NOTE_EXPRESSION_VIBRATO = 3,
   WCLAP_NOTE_EXPRESSION_EXPRESSION = 4,
   WCLAP_NOTE_EXPRESSION_BRIGHTNESS = 5,
   WCLAP_NOTE_EXPRESSION_PRESSURE = 6,
};
typedef int32_t wclap_note_expression;
typedef struct wclap_event_note_expression {
   wclap_event_header header;
   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double value;
} wclap_event_note_expression;
typedef struct wclap_event_param_value {
   wclap_event_header header;
   wclap_id param_id;
   Pointer<void> cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double value;
} wclap_event_param_value;
typedef struct wclap_event_param_mod {
   wclap_event_header header;
   wclap_id param_id;
   Pointer<void> cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double amount;
} wclap_event_param_mod;
typedef struct wclap_event_param_gesture {
   wclap_event_header header;
   wclap_id param_id;
} wclap_event_param_gesture;
enum wclap_transport_flags {
   WCLAP_TRANSPORT_HAS_TEMPO = 1 << 0,
   WCLAP_TRANSPORT_HAS_BEATS_TIMELINE = 1 << 1,
   WCLAP_TRANSPORT_HAS_SECONDS_TIMELINE = 1 << 2,
   WCLAP_TRANSPORT_HAS_TIME_SIGNATURE = 1 << 3,
   WCLAP_TRANSPORT_IS_PLAYING = 1 << 4,
   WCLAP_TRANSPORT_IS_RECORDING = 1 << 5,
   WCLAP_TRANSPORT_IS_LOOP_ACTIVE = 1 << 6,
   WCLAP_TRANSPORT_IS_WITHIN_PRE_ROLL = 1 << 7,
};
typedef struct wclap_event_transport {
   wclap_event_header header;
   uint32_t flags;
   wclap_beattime song_pos_beats;
   wclap_sectime song_pos_seconds;
   double tempo;
   double tempo_inc;
   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime loop_start_seconds;
   wclap_sectime loop_end_seconds;
   wclap_beattime bar_start;
   int32_t bar_number;
   uint16_t tsig_num;
   uint16_t tsig_denom;
} wclap_event_transport;
typedef struct wclap_event_midi {
   wclap_event_header header;
   uint16_t port_index;
   uint8_t data[3];
} wclap_event_midi;
typedef struct wclap_event_midi_sysex {
   wclap_event_header header;
   uint16_t port_index;
   Pointer<const uint8_t> buffer;
   uint32_t size;
} wclap_event_midi_sysex;
typedef struct wclap_event_midi2 {
   wclap_event_header header;
   uint16_t port_index;
   uint32_t data[4];
} wclap_event_midi2;
typedef struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t, Pointer<const struct wclap_input_events>> size;
   Function<Pointer<const wclap_event_header>, Pointer<const struct wclap_input_events>, uint32_t> get;
} wclap_input_events;
typedef struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool, Pointer<const struct wclap_output_events>, Pointer<const wclap_event_header>> try_push;
} wclap_output_events;

//---------- audio-buffer.h

typedef struct wclap_audio_buffer {
   Pointer<Pointer<float>> data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
} wclap_audio_buffer;

//---------- process.h

enum {
   WCLAP_PROCESS_ERROR = 0,
   WCLAP_PROCESS_CONTINUE = 1,
   WCLAP_PROCESS_CONTINUE_IF_NOT_QUIET = 2,
   WCLAP_PROCESS_TAIL = 3,
   WCLAP_PROCESS_SLEEP = 4,
};
typedef int32_t wclap_process_status;
typedef struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport> transport;
   Pointer<const wclap_audio_buffer> audio_inputs;
   Pointer<wclap_audio_buffer> audio_outputs;
   uint32_t audio_inputs_count;
   uint32_t audio_outputs_count;
   Pointer<const wclap_input_events> in_events;
   Pointer<const wclap_output_events> out_events;
} wclap_process;

//---------- plugin-features.h


//---------- plugin.h

typedef struct wclap_plugin_descriptor {
   wclap_version wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<Pointer<const char> const> features;
} wclap_plugin_descriptor;
typedef struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor> desc;
   Pointer<void> plugin_data;
   Function<bool, Pointer<const struct wclap_plugin>> init;
   Function<void, Pointer<const struct wclap_plugin>> destroy;
   Function<bool, Pointer<const struct wclap_plugin>, double, uint32_t, uint32_t> activate;
   Function<void, Pointer<const struct wclap_plugin>> deactivate;
   Function<bool, Pointer<const struct wclap_plugin>> start_processing;
   Function<void, Pointer<const struct wclap_plugin>> stop_processing;
   Function<void, Pointer<const struct wclap_plugin>> reset;
   Function<wclap_process_status, Pointer<const struct wclap_plugin>, Pointer<const wclap_process>> process;
   Function<Pointer<const void>, Pointer<const struct wclap_plugin>, Pointer<const char>> get_extension;
   Function<void, Pointer<const struct wclap_plugin>> on_main_thread;
} wclap_plugin;

//---------- factory/plugin-factory.h

static const WCLAP_CONSTEXPR char WCLAP_PLUGIN_FACTORY_ID[] = "clap.plugin-factory";
typedef struct wclap_plugin_factory {
   Function<uint32_t, Pointer<const struct wclap_plugin_factory>> get_plugin_count;
   Function<Pointer<const wclap_plugin_descriptor>, Pointer<const struct wclap_plugin_factory>, uint32_t> get_plugin_descriptor;
   Function<Pointer<const wclap_plugin>, Pointer<const struct wclap_plugin_factory>, Pointer<const wclap_host>, Pointer<const char>> create_plugin;
} wclap_plugin_factory;

//---------- timestamp.h

typedef uint64_t wclap_timestamp;
static const WCLAP_CONSTEXPR wclap_timestamp WCLAP_TIMESTAMP_UNKNOWN = 0;

//---------- universal-plugin-id.h

typedef struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
} wclap_universal_plugin_id;

//---------- factory/preset-discovery.h

static const WCLAP_CONSTEXPR char WCLAP_PRESET_DISCOVERY_FACTORY_ID[] =
   "clap.preset-discovery-factory/2";
static const WCLAP_CONSTEXPR char WCLAP_PRESET_DISCOVERY_FACTORY_ID_COMPAT[] =
   "clap.preset-discovery-factory/draft-2";
enum wclap_preset_discovery_location_kind {
   WCLAP_PRESET_DISCOVERY_LOCATION_FILE = 0,
   WCLAP_PRESET_DISCOVERY_LOCATION_PLUGIN = 1,
};
enum wclap_preset_discovery_flags {
   WCLAP_PRESET_DISCOVERY_IS_FACTORY_CONTENT = 1 << 0,
   WCLAP_PRESET_DISCOVERY_IS_USER_CONTENT = 1 << 1,
   WCLAP_PRESET_DISCOVERY_IS_DEMO_CONTENT = 1 << 2,
   WCLAP_PRESET_DISCOVERY_IS_FAVORITE = 1 << 3,
};
typedef struct wclap_preset_discovery_metadata_receiver {
   Pointer<void> receiver_data;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, int32_t, Pointer<const char>> on_error;
   Function<bool, Pointer<const struct wclap_preset_discovery_metadata_receiver>, Pointer<const char>, Pointer<const char>> begin_preset;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, Pointer<const wclap_universal_plugin_id>> add_plugin_id;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, Pointer<const char>> set_soundpack_id;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, uint32_t> set_flags;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, Pointer<const char>> add_creator;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, Pointer<const char>> set_description;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, wclap_timestamp, wclap_timestamp> set_timestamps;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, Pointer<const char>> add_feature;
   Function<void, Pointer<const struct wclap_preset_discovery_metadata_receiver>, Pointer<const char>, Pointer<const char>> add_extra_info;
} wclap_preset_discovery_metadata_receiver;
typedef struct wclap_preset_discovery_filetype {
   Pointer<const char> name;
   Pointer<const char> description;
   Pointer<const char> file_extension;
} wclap_preset_discovery_filetype;
typedef struct wclap_preset_discovery_location {
   uint32_t flags;
   Pointer<const char> name;
   uint32_t kind;
   Pointer<const char> location;
} wclap_preset_discovery_location;
typedef struct wclap_preset_discovery_soundpack {
   uint32_t flags;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> description;
   Pointer<const char> homepage_url;
   Pointer<const char> vendor;
   Pointer<const char> image_path;
   wclap_timestamp release_timestamp;
} wclap_preset_discovery_soundpack;
typedef struct wclap_preset_discovery_provider_descriptor {
   wclap_version wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
} wclap_preset_discovery_provider_descriptor;
typedef struct wclap_preset_discovery_provider {
   Pointer<const wclap_preset_discovery_provider_descriptor> desc;
   Pointer<void> provider_data;
   Function<bool, Pointer<const struct wclap_preset_discovery_provider>> init;
   Function<void, Pointer<const struct wclap_preset_discovery_provider>> destroy;
   Function<bool, Pointer<const struct wclap_preset_discovery_provider>, uint32_t, Pointer<const char>, Pointer<const wclap_preset_discovery_metadata_receiver>> get_metadata;
   Function<Pointer<const void>, Pointer<const struct wclap_preset_discovery_provider>, Pointer<const char>> get_extension;
} wclap_preset_discovery_provider;
typedef struct wclap_preset_discovery_indexer {
   wclap_version wclap_version;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Pointer<void> indexer_data;
   Function<bool, Pointer<const struct wclap_preset_discovery_indexer>, Pointer<const wclap_preset_discovery_filetype>> declare_filetype;
   Function<bool, Pointer<const struct wclap_preset_discovery_indexer>, Pointer<const wclap_preset_discovery_location>> declare_location;
   Function<bool, Pointer<const struct wclap_preset_discovery_indexer>, Pointer<const wclap_preset_discovery_soundpack>> declare_soundpack;
   Function<Pointer<const void>, Pointer<const struct wclap_preset_discovery_indexer>, Pointer<const char>> get_extension;
} wclap_preset_discovery_indexer;
typedef struct wclap_preset_discovery_factory {
   Function<uint32_t, Pointer<const struct wclap_preset_discovery_factory>> count;
   Function<Pointer<const wclap_preset_discovery_provider_descriptor>, Pointer<const struct wclap_preset_discovery_factory>, uint32_t> get_descriptor;
   Function<Pointer<const wclap_preset_discovery_provider>, Pointer<const struct wclap_preset_discovery_factory>, Pointer<const wclap_preset_discovery_indexer>, Pointer<const char>> create;
} wclap_preset_discovery_factory;

//---------- ext/ambisonic.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_AMBISONIC[] = "clap.ambisonic/3";
static WCLAP_CONSTEXPR const char WCLAP_EXT_AMBISONIC_COMPAT[] = "clap.ambisonic.draft/3";
static WCLAP_CONSTEXPR const char WCLAP_PORT_AMBISONIC[] = "ambisonic";
enum wclap_ambisonic_ordering {
   WCLAP_AMBISONIC_ORDERING_FUMA = 0,
   WCLAP_AMBISONIC_ORDERING_ACN = 1,
};
enum wclap_ambisonic_normalization {
   WCLAP_AMBISONIC_NORMALIZATION_MAXN = 0,
   WCLAP_AMBISONIC_NORMALIZATION_SN3D = 1,
   WCLAP_AMBISONIC_NORMALIZATION_N3D = 2,
   WCLAP_AMBISONIC_NORMALIZATION_SN2D = 3,
   WCLAP_AMBISONIC_NORMALIZATION_N2D = 4,
};
typedef struct wclap_ambisonic_config {
   uint32_t ordering;
   uint32_t normalization;
} wclap_ambisonic_config;
typedef struct wclap_plugin_ambisonic {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_ambisonic_config>> is_config_supported;
   Function<bool, Pointer<const wclap_plugin>, bool, uint32_t, Pointer<wclap_ambisonic_config>> get_config;
} wclap_plugin_ambisonic;
typedef struct wclap_host_ambisonic {
   Function<void, Pointer<const wclap_host>> changed;
} wclap_host_ambisonic;

//---------- ext/audio-ports-activation.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_AUDIO_PORTS_ACTIVATION[] =
   "clap.audio-ports-activation/2";
static WCLAP_CONSTEXPR const char WCLAP_EXT_AUDIO_PORTS_ACTIVATION_COMPAT[] =
   "clap.audio-ports-activation/draft-2";
typedef struct wclap_plugin_audio_ports_activation {
   Function<bool, Pointer<const wclap_plugin>> can_activate_while_processing;
   Function<bool, Pointer<const wclap_plugin>, bool, uint32_t, bool, uint32_t> set_active;
} wclap_plugin_audio_ports_activation;

//---------- string-sizes.h

enum {
   WCLAP_NAME_SIZE = 256,
   WCLAP_PATH_SIZE = 1024,
};

//---------- ext/audio-ports.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_AUDIO_PORTS[] = "clap.audio-ports";
static WCLAP_CONSTEXPR const char WCLAP_PORT_MONO[] = "mono";
static WCLAP_CONSTEXPR const char WCLAP_PORT_STEREO[] = "stereo";
enum {
   WCLAP_AUDIO_PORT_IS_MAIN = 1 << 0,
   WCLAP_AUDIO_PORT_SUPPORTS_64BITS = 1 << 1,
   WCLAP_AUDIO_PORT_PREFERS_64BITS = 1 << 2,
   WCLAP_AUDIO_PORT_REQUIRES_COMMON_SAMPLE_SIZE = 1 << 3,
};
typedef struct wclap_audio_port_info {
   wclap_id id;
   char name[WCLAP_NAME_SIZE];
   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
} wclap_audio_port_info;
typedef struct wclap_plugin_audio_ports {
   Function<uint32_t, Pointer<const wclap_plugin>, bool> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, bool, Pointer<wclap_audio_port_info>> get;
} wclap_plugin_audio_ports;
enum {
   WCLAP_AUDIO_PORTS_RESCAN_NAMES = 1 << 0,
   WCLAP_AUDIO_PORTS_RESCAN_FLAGS = 1 << 1,
   WCLAP_AUDIO_PORTS_RESCAN_CHANNEL_COUNT = 1 << 2,
   WCLAP_AUDIO_PORTS_RESCAN_PORT_TYPE = 1 << 3,
   WCLAP_AUDIO_PORTS_RESCAN_IN_PLACE_PAIR = 1 << 4,
   WCLAP_AUDIO_PORTS_RESCAN_LIST = 1 << 5,
};
typedef struct wclap_host_audio_ports {
   Function<bool, Pointer<const wclap_host>, uint32_t> is_rescan_flag_supported;
   Function<void, Pointer<const wclap_host>, uint32_t> rescan;
} wclap_host_audio_ports;

//---------- ext/audio-ports-config.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_AUDIO_PORTS_CONFIG[] = "clap.audio-ports-config";
static WCLAP_CONSTEXPR const char WCLAP_EXT_AUDIO_PORTS_CONFIG_INFO[] =
   "clap.audio-ports-config-info/1";
static WCLAP_CONSTEXPR const char WCLAP_EXT_AUDIO_PORTS_CONFIG_INFO_COMPAT[] =
   "clap.audio-ports-config-info/draft-0";
typedef struct wclap_audio_ports_config {
   wclap_id id;
   char name[WCLAP_NAME_SIZE];
   uint32_t input_port_count;
   uint32_t output_port_count;
   bool has_main_input;
   uint32_t main_input_channel_count;
   Pointer<const char> main_input_port_type;
   bool has_main_output;
   uint32_t main_output_channel_count;
   Pointer<const char> main_output_port_type;
} wclap_audio_ports_config;
typedef struct wclap_plugin_audio_ports_config {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_audio_ports_config>> get;
   Function<bool, Pointer<const wclap_plugin>, wclap_id> select;
} wclap_plugin_audio_ports_config;
typedef struct wclap_plugin_audio_ports_config_info {
   Function<wclap_id, Pointer<const wclap_plugin>> current_config;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, uint32_t, bool, Pointer<wclap_audio_port_info>> get;
} wclap_plugin_audio_ports_config_info;
typedef struct wclap_host_audio_ports_config {
   Function<void, Pointer<const wclap_host>> rescan;
} wclap_host_audio_ports_config;

//---------- ext/configurable-audio-ports.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_CONFIGURABLE_AUDIO_PORTS[] =
   "clap.configurable-audio-ports/1";
static WCLAP_CONSTEXPR const char WCLAP_EXT_CONFIGURABLE_AUDIO_PORTS_COMPAT[] =
   "clap.configurable-audio-ports.draft1";
typedef struct wclap_audio_port_configuration_request {
   bool is_input;
   uint32_t port_index;
   uint32_t channel_count;
   Pointer<const char> port_type;
   Pointer<const void> port_details;
} wclap_audio_port_configuration_request;
typedef struct wclap_plugin_configurable_audio_ports {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const struct wclap_audio_port_configuration_request>, uint32_t> can_apply_configuration;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const struct wclap_audio_port_configuration_request>, uint32_t> apply_configuration;
} wclap_plugin_configurable_audio_ports;

//---------- ext/context-menu.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_CONTEXT_MENU[] = "clap.context-menu/1";
static WCLAP_CONSTEXPR const char WCLAP_EXT_CONTEXT_MENU_COMPAT[] = "clap.context-menu.draft/0";
enum {
   WCLAP_CONTEXT_MENU_TARGET_KIND_GLOBAL = 0,
   WCLAP_CONTEXT_MENU_TARGET_KIND_PARAM = 1,
};
typedef struct wclap_context_menu_target {
   uint32_t kind;
   wclap_id id;
} wclap_context_menu_target;
enum {
   WCLAP_CONTEXT_MENU_ITEM_ENTRY,
   WCLAP_CONTEXT_MENU_ITEM_CHECK_ENTRY,
   WCLAP_CONTEXT_MENU_ITEM_SEPARATOR,
   WCLAP_CONTEXT_MENU_ITEM_BEGIN_SUBMENU,
   WCLAP_CONTEXT_MENU_ITEM_END_SUBMENU,
   WCLAP_CONTEXT_MENU_ITEM_TITLE,
};
typedef uint32_t wclap_context_menu_item_kind;
typedef struct wclap_context_menu_entry {
   Pointer<const char> label;
   bool is_enabled;
   wclap_id action_id;
} wclap_context_menu_entry;
typedef struct wclap_context_menu_check_entry {
   Pointer<const char> label;
   bool is_enabled;
   bool is_checked;
   wclap_id action_id;
} wclap_context_menu_check_entry;
typedef struct wclap_context_menu_item_title {
   Pointer<const char> title;
   bool is_enabled;
} wclap_context_menu_item_title;
typedef struct wclap_context_menu_submenu {
   Pointer<const char> label;
   bool is_enabled;
} wclap_context_menu_submenu;
typedef struct wclap_context_menu_builder {
   Pointer<void> ctx;
   Function<bool, Pointer<const struct wclap_context_menu_builder>, wclap_context_menu_item_kind, Pointer<const void>> add_item;
   Function<bool, Pointer<const struct wclap_context_menu_builder>, wclap_context_menu_item_kind> supports;
} wclap_context_menu_builder;
typedef struct wclap_plugin_context_menu {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_context_menu_target>, Pointer<const wclap_context_menu_builder>> populate;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_context_menu_target>, wclap_id> perform;
} wclap_plugin_context_menu;
typedef struct wclap_host_context_menu {
   Function<bool, Pointer<const wclap_host>, Pointer<const wclap_context_menu_target>, Pointer<const wclap_context_menu_builder>> populate;
   Function<bool, Pointer<const wclap_host>, Pointer<const wclap_context_menu_target>, wclap_id> perform;
   Function<bool, Pointer<const wclap_host>> can_popup;
   Function<bool, Pointer<const wclap_host>, Pointer<const wclap_context_menu_target>, int32_t, int32_t, int32_t> popup;
} wclap_host_context_menu;

//---------- ext/event-registry.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_EVENT_REGISTRY[] = "clap.event-registry";
typedef struct wclap_host_event_registry {
   Function<bool, Pointer<const wclap_host>, Pointer<const char>, Pointer<uint16_t>> query;
} wclap_host_event_registry;

//---------- ext/gui.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_GUI[] = "clap.gui";
static const WCLAP_CONSTEXPR char WCLAP_WINDOW_API_WIN32[] = "win32";
static const WCLAP_CONSTEXPR char WCLAP_WINDOW_API_COCOA[] = "cocoa";
static const WCLAP_CONSTEXPR char WCLAP_WINDOW_API_X11[] = "x11";
static const WCLAP_CONSTEXPR char WCLAP_WINDOW_API_WAYLAND[] = "wayland";
typedef Pointer<void> wclap_hwnd;
typedef Pointer<void> wclap_nsview;
typedef unsigned long wclap_xwnd;
typedef struct wclap_window {
   Pointer<const char> api;
   union {
      wclap_nsview cocoa;
      wclap_xwnd x11;
      wclap_hwnd win32;
      Pointer<void> ptr;
   };
} wclap_window;
typedef struct wclap_gui_resize_hints {
   bool can_resize_horizontally;
   bool can_resize_vertically;
   bool preserve_aspect_ratio;
   uint32_t aspect_ratio_width;
   uint32_t aspect_ratio_height;
} wclap_gui_resize_hints;
typedef struct wclap_plugin_gui {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const char>, bool> is_api_supported;
   Function<bool, Pointer<const wclap_plugin>, Pointer<Pointer<const char>>, Pointer<bool>> get_preferred_api;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const char>, bool> create;
   Function<void, Pointer<const wclap_plugin>> destroy;
   Function<bool, Pointer<const wclap_plugin>, double> set_scale;
   Function<bool, Pointer<const wclap_plugin>, Pointer<uint32_t>, Pointer<uint32_t>> get_size;
   Function<bool, Pointer<const wclap_plugin>> can_resize;
   Function<bool, Pointer<const wclap_plugin>, Pointer<wclap_gui_resize_hints>> get_resize_hints;
   Function<bool, Pointer<const wclap_plugin>, Pointer<uint32_t>, Pointer<uint32_t>> adjust_size;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, uint32_t> set_size;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_window>> set_parent;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_window>> set_transient;
   Function<void, Pointer<const wclap_plugin>, Pointer<const char>> suggest_title;
   Function<bool, Pointer<const wclap_plugin>> show;
   Function<bool, Pointer<const wclap_plugin>> hide;
} wclap_plugin_gui;
typedef struct wclap_host_gui {
   Function<void, Pointer<const wclap_host>> resize_hints_changed;
   Function<bool, Pointer<const wclap_host>, uint32_t, uint32_t> request_resize;
   Function<bool, Pointer<const wclap_host>> request_show;
   Function<bool, Pointer<const wclap_host>> request_hide;
   Function<void, Pointer<const wclap_host>, bool> closed;
} wclap_host_gui;

//---------- ext/latency.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_LATENCY[] = "clap.latency";
typedef struct wclap_plugin_latency {
   Function<uint32_t, Pointer<const wclap_plugin>> get;
} wclap_plugin_latency;
typedef struct wclap_host_latency {
   Function<void, Pointer<const wclap_host>> changed;
} wclap_host_latency;

//---------- ext/log.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_LOG[] = "clap.log";
enum {
   WCLAP_LOG_DEBUG = 0,
   WCLAP_LOG_INFO = 1,
   WCLAP_LOG_WARNING = 2,
   WCLAP_LOG_ERROR = 3,
   WCLAP_LOG_FATAL = 4,
   WCLAP_LOG_HOST_MISBEHAVING = 5,
   WCLAP_LOG_PLUGIN_MISBEHAVING = 6,
};
typedef int32_t wclap_log_severity;
typedef struct wclap_host_log {
   Function<void, Pointer<const wclap_host>, wclap_log_severity, Pointer<const char>> log;
} wclap_host_log;

//---------- ext/note-name.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_NOTE_NAME[] = "clap.note-name";
typedef struct wclap_note_name {
   char name[WCLAP_NAME_SIZE];
   int16_t port;
   int16_t key;
   int16_t channel;
} wclap_note_name;
typedef struct wclap_plugin_note_name {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_note_name>> get;
} wclap_plugin_note_name;
typedef struct wclap_host_note_name {
   Function<void, Pointer<const wclap_host>> changed;
} wclap_host_note_name;

//---------- ext/note-ports.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_NOTE_PORTS[] = "clap.note-ports";
enum wclap_note_dialect {
   WCLAP_NOTE_DIALECT_CLAP = 1 << 0,
   WCLAP_NOTE_DIALECT_MIDI = 1 << 1,
   WCLAP_NOTE_DIALECT_MIDI_MPE = 1 << 2,
   WCLAP_NOTE_DIALECT_MIDI2 = 1 << 3,
};
typedef struct wclap_note_port_info {
   wclap_id id;
   uint32_t supported_dialects;
   uint32_t preferred_dialect;
   char name[WCLAP_NAME_SIZE];
} wclap_note_port_info;
typedef struct wclap_plugin_note_ports {
   Function<uint32_t, Pointer<const wclap_plugin>, bool> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, bool, Pointer<wclap_note_port_info>> get;
} wclap_plugin_note_ports;
enum {
   WCLAP_NOTE_PORTS_RESCAN_ALL = 1 << 0,
   WCLAP_NOTE_PORTS_RESCAN_NAMES = 1 << 1,
};
typedef struct wclap_host_note_ports {
   Function<uint32_t, Pointer<const wclap_host>> supported_dialects;
   Function<void, Pointer<const wclap_host>, uint32_t> rescan;
} wclap_host_note_ports;

//---------- ext/params.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_PARAMS[] = "clap.params";
enum {
   WCLAP_PARAM_IS_STEPPED = 1 << 0,
   WCLAP_PARAM_IS_PERIODIC = 1 << 1,
   WCLAP_PARAM_IS_HIDDEN = 1 << 2,
   WCLAP_PARAM_IS_READONLY = 1 << 3,
   WCLAP_PARAM_IS_BYPASS = 1 << 4,
   WCLAP_PARAM_IS_AUTOMATABLE = 1 << 5,
   WCLAP_PARAM_IS_AUTOMATABLE_PER_NOTE_ID = 1 << 6,
   WCLAP_PARAM_IS_AUTOMATABLE_PER_KEY = 1 << 7,
   WCLAP_PARAM_IS_AUTOMATABLE_PER_CHANNEL = 1 << 8,
   WCLAP_PARAM_IS_AUTOMATABLE_PER_PORT = 1 << 9,
   WCLAP_PARAM_IS_MODULATABLE = 1 << 10,
   WCLAP_PARAM_IS_MODULATABLE_PER_NOTE_ID = 1 << 11,
   WCLAP_PARAM_IS_MODULATABLE_PER_KEY = 1 << 12,
   WCLAP_PARAM_IS_MODULATABLE_PER_CHANNEL = 1 << 13,
   WCLAP_PARAM_IS_MODULATABLE_PER_PORT = 1 << 14,
   WCLAP_PARAM_REQUIRES_PROCESS = 1 << 15,
   WCLAP_PARAM_IS_ENUM = 1 << 16,
};
typedef uint32_t wclap_param_info_flags;
typedef struct wclap_param_info {
   wclap_id id;
   wclap_param_info_flags flags;
   Pointer<void> cookie;
   char name[WCLAP_NAME_SIZE];
   char module[WCLAP_PATH_SIZE];
   double min_value;
   double max_value;
   double default_value;
} wclap_param_info;
typedef struct wclap_plugin_params {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_param_info>> get_info;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, Pointer<double>> get_value;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, double, Pointer<char>, uint32_t> value_to_text;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, Pointer<const char>, Pointer<double>> text_to_value;
   Function<void, Pointer<const wclap_plugin>, Pointer<const wclap_input_events>, Pointer<const wclap_output_events>> flush;
} wclap_plugin_params;
enum {
   WCLAP_PARAM_RESCAN_VALUES = 1 << 0,
   WCLAP_PARAM_RESCAN_TEXT = 1 << 1,
   WCLAP_PARAM_RESCAN_INFO = 1 << 2,
   WCLAP_PARAM_RESCAN_ALL = 1 << 3,
};
typedef uint32_t wclap_param_rescan_flags;
enum {
   WCLAP_PARAM_CLEAR_ALL = 1 << 0,
   WCLAP_PARAM_CLEAR_AUTOMATIONS = 1 << 1,
   WCLAP_PARAM_CLEAR_MODULATIONS = 1 << 2,
};
typedef uint32_t wclap_param_clear_flags;
typedef struct wclap_host_params {
   Function<void, Pointer<const wclap_host>, wclap_param_rescan_flags> rescan;
   Function<void, Pointer<const wclap_host>, wclap_id, wclap_param_clear_flags> clear;
   Function<void, Pointer<const wclap_host>> request_flush;
} wclap_host_params;

//---------- color.h

typedef struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
} wclap_color;
static const WCLAP_CONSTEXPR wclap_color WCLAP_COLOR_TRANSPARENT = { 0, 0, 0, 0 };

//---------- ext/param-indication.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_PARAM_INDICATION[] = "clap.param-indication/4";
static WCLAP_CONSTEXPR const char WCLAP_EXT_PARAM_INDICATION_COMPAT[] = "clap.param-indication.draft/4";
enum {
   WCLAP_PARAM_INDICATION_AUTOMATION_NONE = 0,
   WCLAP_PARAM_INDICATION_AUTOMATION_PRESENT = 1,
   WCLAP_PARAM_INDICATION_AUTOMATION_PLAYING = 2,
   WCLAP_PARAM_INDICATION_AUTOMATION_RECORDING = 3,
   WCLAP_PARAM_INDICATION_AUTOMATION_OVERRIDING = 4,
};
typedef struct wclap_plugin_param_indication {
   Function<void, Pointer<const wclap_plugin>, wclap_id, bool, Pointer<const wclap_color>, Pointer<const char>, Pointer<const char>> set_mapping;
   Function<void, Pointer<const wclap_plugin>, wclap_id, uint32_t, Pointer<const wclap_color>> set_automation;
} wclap_plugin_param_indication;

//---------- ext/posix-fd-support.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_POSIX_FD_SUPPORT[] = "clap.posix-fd-support";
enum {
   WCLAP_POSIX_FD_READ = 1 << 0,
   WCLAP_POSIX_FD_WRITE = 1 << 1,
   WCLAP_POSIX_FD_ERROR = 1 << 2,
};
typedef uint32_t wclap_posix_fd_flags;
typedef struct wclap_plugin_posix_fd_support {
   Function<void, Pointer<const wclap_plugin>, int, wclap_posix_fd_flags> on_fd;
} wclap_plugin_posix_fd_support;
typedef struct wclap_host_posix_fd_support {
   Function<bool, Pointer<const wclap_host>, int, wclap_posix_fd_flags> register_fd;
   Function<bool, Pointer<const wclap_host>, int, wclap_posix_fd_flags> modify_fd;
   Function<bool, Pointer<const wclap_host>, int> unregister_fd;
} wclap_host_posix_fd_support;

//---------- ext/preset-load.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_PRESET_LOAD[] = "clap.preset-load/2";
static WCLAP_CONSTEXPR const char WCLAP_EXT_PRESET_LOAD_COMPAT[] = "clap.preset-load.draft/2";
typedef struct wclap_plugin_preset_load {
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<const char>, Pointer<const char>> from_location;
} wclap_plugin_preset_load;
typedef struct wclap_host_preset_load {
   Function<void, Pointer<const wclap_host>, uint32_t, Pointer<const char>, Pointer<const char>, int32_t, Pointer<const char>> on_error;
   Function<void, Pointer<const wclap_host>, uint32_t, Pointer<const char>, Pointer<const char>> loaded;
} wclap_host_preset_load;

//---------- ext/remote-controls.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_REMOTE_CONTROLS[] = "clap.remote-controls/2";
static WCLAP_CONSTEXPR const char WCLAP_EXT_REMOTE_CONTROLS_COMPAT[] = "clap.remote-controls.draft/2";
enum { WCLAP_REMOTE_CONTROLS_COUNT = 8 };
typedef struct wclap_remote_controls_page {
   char section_name[WCLAP_NAME_SIZE];
   wclap_id page_id;
   char page_name[WCLAP_NAME_SIZE];
   wclap_id param_ids[WCLAP_REMOTE_CONTROLS_COUNT];
   bool is_for_preset;
} wclap_remote_controls_page;
typedef struct wclap_plugin_remote_controls {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_remote_controls_page>> get;
} wclap_plugin_remote_controls;
typedef struct wclap_host_remote_controls {
   Function<void, Pointer<const wclap_host>> changed;
   Function<void, Pointer<const wclap_host>, wclap_id> suggest_page;
} wclap_host_remote_controls;

//---------- ext/render.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_RENDER[] = "clap.render";
enum {
   WCLAP_RENDER_REALTIME = 0,
   WCLAP_RENDER_OFFLINE = 1,
};
typedef int32_t wclap_plugin_render_mode;
typedef struct wclap_plugin_render {
   Function<bool, Pointer<const wclap_plugin>> has_hard_realtime_requirement;
   Function<bool, Pointer<const wclap_plugin>, wclap_plugin_render_mode> set;
} wclap_plugin_render;

//---------- stream.h

typedef struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t, Pointer<const struct wclap_istream>, Pointer<void>, uint64_t> read;
} wclap_istream;
typedef struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t, Pointer<const struct wclap_ostream>, Pointer<const void>, uint64_t> write;
} wclap_ostream;

//---------- ext/state-context.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_STATE_CONTEXT[] = "clap.state-context/2";
enum wclap_plugin_state_context_type {
   WCLAP_STATE_CONTEXT_FOR_PRESET = 1,
   WCLAP_STATE_CONTEXT_FOR_DUPLICATE = 2,
   WCLAP_STATE_CONTEXT_FOR_PROJECT = 3,
};
typedef struct wclap_plugin_state_context {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_ostream>, uint32_t> save;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_istream>, uint32_t> load;
} wclap_plugin_state_context;

//---------- ext/state.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_STATE[] = "clap.state";
typedef struct wclap_plugin_state {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_ostream>> save;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_istream>> load;
} wclap_plugin_state;
typedef struct wclap_host_state {
   Function<void, Pointer<const wclap_host>> mark_dirty;
} wclap_host_state;

//---------- ext/surround.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_SURROUND[] = "clap.surround/4";
static WCLAP_CONSTEXPR const char WCLAP_EXT_SURROUND_COMPAT[] = "clap.surround.draft/4";
static WCLAP_CONSTEXPR const char WCLAP_PORT_SURROUND[] = "surround";
enum {
   WCLAP_SURROUND_FL = 0,
   WCLAP_SURROUND_FR = 1,
   WCLAP_SURROUND_FC = 2,
   WCLAP_SURROUND_LFE = 3,
   WCLAP_SURROUND_BL = 4,
   WCLAP_SURROUND_BR = 5,
   WCLAP_SURROUND_FLC = 6,
   WCLAP_SURROUND_FRC = 7,
   WCLAP_SURROUND_BC = 8,
   WCLAP_SURROUND_SL = 9,
   WCLAP_SURROUND_SR = 10,
   WCLAP_SURROUND_TC = 11,
   WCLAP_SURROUND_TFL = 12,
   WCLAP_SURROUND_TFC = 13,
   WCLAP_SURROUND_TFR = 14,
   WCLAP_SURROUND_TBL = 15,
   WCLAP_SURROUND_TBC = 16,
   WCLAP_SURROUND_TBR = 17,
   WCLAP_SURROUND_TSL = 18,
   WCLAP_SURROUND_TSR = 19,
};
typedef struct wclap_plugin_surround {
   Function<bool, Pointer<const wclap_plugin>, uint64_t> is_channel_mask_supported;
   Function<uint32_t, Pointer<const wclap_plugin>, bool, uint32_t, Pointer<uint8_t>, uint32_t> get_channel_map;
} wclap_plugin_surround;
typedef struct wclap_host_surround {
   Function<void, Pointer<const wclap_host>> changed;
} wclap_host_surround;

//---------- ext/tail.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_TAIL[] = "clap.tail";
typedef struct wclap_plugin_tail {
   Function<uint32_t, Pointer<const wclap_plugin>> get;
} wclap_plugin_tail;
typedef struct wclap_host_tail {
   Function<void, Pointer<const wclap_host>> changed;
} wclap_host_tail;

//---------- ext/thread-check.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_THREAD_CHECK[] = "clap.thread-check";
typedef struct wclap_host_thread_check {
   Function<bool, Pointer<const wclap_host>> is_main_thread;
   Function<bool, Pointer<const wclap_host>> is_audio_thread;
} wclap_host_thread_check;

//---------- ext/thread-pool.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_THREAD_POOL[] = "clap.thread-pool";
typedef struct wclap_plugin_thread_pool {
   Function<void, Pointer<const wclap_plugin>, uint32_t> exec;
} wclap_plugin_thread_pool;
typedef struct wclap_host_thread_pool {
   Function<bool, Pointer<const wclap_host>, uint32_t> request_exec;
} wclap_host_thread_pool;

//---------- ext/timer-support.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_TIMER_SUPPORT[] = "clap.timer-support";
typedef struct wclap_plugin_timer_support {
   Function<void, Pointer<const wclap_plugin>, wclap_id> on_timer;
} wclap_plugin_timer_support;
typedef struct wclap_host_timer_support {
   Function<bool, Pointer<const wclap_host>, uint32_t, Pointer<wclap_id>> register_timer;
   Function<bool, Pointer<const wclap_host>, wclap_id> unregister_timer;
} wclap_host_timer_support;

//---------- ext/track-info.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_TRACK_INFO[] = "clap.track-info/1";
static WCLAP_CONSTEXPR const char WCLAP_EXT_TRACK_INFO_COMPAT[] = "clap.track-info.draft/1";
enum {
   WCLAP_TRACK_INFO_HAS_TRACK_NAME = (1 << 0),
   WCLAP_TRACK_INFO_HAS_TRACK_COLOR = (1 << 1),
   WCLAP_TRACK_INFO_HAS_AUDIO_CHANNEL = (1 << 2),
   WCLAP_TRACK_INFO_IS_FOR_RETURN_TRACK = (1 << 3),
   WCLAP_TRACK_INFO_IS_FOR_BUS = (1 << 4),
   WCLAP_TRACK_INFO_IS_FOR_MASTER = (1 << 5),
};
typedef struct wclap_track_info {
   uint64_t flags;
   char name[WCLAP_NAME_SIZE];
   wclap_color color;
   int32_t audio_channel_count;
   Pointer<const char> audio_port_type;
} wclap_track_info;
typedef struct wclap_plugin_track_info {
   Function<void, Pointer<const wclap_plugin>> changed;
} wclap_plugin_track_info;
typedef struct wclap_host_track_info {
   Function<bool, Pointer<const wclap_host>, Pointer<wclap_track_info>> get;
} wclap_host_track_info;

//---------- ext/voice-info.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_VOICE_INFO[] = "clap.voice-info";
enum {
   WCLAP_VOICE_INFO_SUPPORTS_OVERLAPPING_NOTES = 1 << 0,
};
typedef struct wclap_voice_info {
   uint32_t voice_count;
   uint32_t voice_capacity;
   uint64_t flags;
} wclap_voice_info;
typedef struct wclap_plugin_voice_info {
   Function<bool, Pointer<const wclap_plugin>, Pointer<wclap_voice_info>> get;
} wclap_plugin_voice_info;
typedef struct wclap_host_voice_info {
   Function<void, Pointer<const wclap_host>> changed;
} wclap_host_voice_info;

//---------- clap.h


//---------- factory/draft/plugin-invalidation.h

static const WCLAP_CONSTEXPR char WCLAP_PLUGIN_INVALIDATION_FACTORY_ID[] =
   "clap.plugin-invalidation-factory/1";
typedef struct wclap_plugin_invalidation_source {
   Pointer<const char> directory;
   Pointer<const char> filename_glob;
   bool recursive_scan;
} wclap_plugin_invalidation_source;
typedef struct wclap_plugin_invalidation_factory {
   Function<uint32_t, Pointer<const struct wclap_plugin_invalidation_factory>> count;
   Function<Pointer<const wclap_plugin_invalidation_source>, Pointer<const struct wclap_plugin_invalidation_factory>, uint32_t> get;
   Function<bool, Pointer<const struct wclap_plugin_invalidation_factory>> refresh;
} wclap_plugin_invalidation_factory;

//---------- factory/draft/plugin-state-converter.h

typedef struct wclap_plugin_state_converter_descriptor {
   wclap_version wclap_version;
   wclap_universal_plugin_id src_plugin_id;
   wclap_universal_plugin_id dst_plugin_id;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> version;
   Pointer<const char> description;
} wclap_plugin_state_converter_descriptor;
typedef struct wclap_plugin_state_converter {
   Pointer<const wclap_plugin_state_converter_descriptor> desc;
   Pointer<void> converter_data;
   Function<void, Pointer<struct wclap_plugin_state_converter>> destroy;
   Function<bool, Pointer<struct wclap_plugin_state_converter>, Pointer<const wclap_istream>, Pointer<const wclap_ostream>, Pointer<char>, size_t> convert_state;
   Function<bool, Pointer<struct wclap_plugin_state_converter>, wclap_id, double, Pointer<wclap_id>, Pointer<double>> convert_normalized_value;
   Function<bool, Pointer<struct wclap_plugin_state_converter>, wclap_id, double, Pointer<wclap_id>, Pointer<double>> convert_plain_value;
} wclap_plugin_state_converter;
static WCLAP_CONSTEXPR const char WCLAP_PLUGIN_STATE_CONVERTER_FACTORY_ID[] =
   "clap.plugin-state-converter-factory/1";
typedef struct wclap_plugin_state_converter_factory {
   Function<uint32_t, Pointer<const struct wclap_plugin_state_converter_factory>> count;
   Function<Pointer<const wclap_plugin_state_converter_descriptor>, Pointer<const struct wclap_plugin_state_converter_factory>, uint32_t> get_descriptor;
   Function<Pointer<wclap_plugin_state_converter>, Pointer<const struct wclap_plugin_state_converter_factory>, Pointer<const char>> create;
} wclap_plugin_state_converter_factory;

//---------- ext/draft/extensible-audio-ports.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_EXTENSIBLE_AUDIO_PORTS[] =
   "clap.extensible-audio-ports/1";
typedef struct wclap_plugin_extensible_audio_ports {
   Function<bool, Pointer<const wclap_plugin>, bool, uint32_t, Pointer<const char>, Pointer<const void>> add_port;
   Function<bool, Pointer<const wclap_plugin>, bool, uint32_t> remove_port;
} wclap_plugin_extensible_audio_ports;

//---------- ext/draft/gain-adjustment-metering.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_GAIN_ADJUSTMENT_METERING[] = "clap.gain-adjustment-metering/0";
typedef struct wclap_plugin_gain_adjustment_metering {
  Function<double, Pointer<const wclap_plugin>> get;
} wclap_plugin_gain_adjustment_metering;

//---------- ext/draft/mini-curve-display.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_MINI_CURVE_DISPLAY[] = "clap.mini-curve-display/3";
enum wclap_mini_curve_display_curve_kind {
   WCLAP_MINI_CURVE_DISPLAY_CURVE_KIND_UNSPECIFIED = 0,
   WCLAP_MINI_CURVE_DISPLAY_CURVE_KIND_GAIN_RESPONSE = 1,
   WCLAP_MINI_CURVE_DISPLAY_CURVE_KIND_PHASE_RESPONSE = 2,
   WCLAP_MINI_CURVE_DISPLAY_CURVE_KIND_TRANSFER_CURVE = 3,
   WCLAP_MINI_CURVE_DISPLAY_CURVE_KIND_GAIN_REDUCTION = 4,
   WCLAP_MINI_CURVE_DISPLAY_CURVE_KIND_TIME_SERIES = 5,
};
typedef struct wclap_mini_curve_display_curve_hints {
   double x_min;
   double x_max;
   double y_min;
   double y_max;
} wclap_mini_curve_display_curve_hints;
typedef struct wclap_mini_curve_display_curve_data {
   int32_t curve_kind;
   Pointer<uint16_t> values;
   uint32_t values_count;
} wclap_mini_curve_display_curve_data;
typedef struct wclap_plugin_mini_curve_display {
   Function<uint32_t, Pointer<const wclap_plugin>> get_curve_count;
   Function<uint32_t, Pointer<const wclap_plugin>, Pointer<wclap_mini_curve_display_curve_data>, uint32_t> render;
   Function<void, Pointer<const wclap_plugin>, bool> set_observed;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<char>, Pointer<char>, uint32_t> get_axis_name;
} wclap_plugin_mini_curve_display;
enum wclap_mini_curve_display_change_flags {
   WCLAP_MINI_CURVE_DISPLAY_CURVE_CHANGED = 1 << 0,
   WCLAP_MINI_CURVE_DISPLAY_AXIS_NAME_CHANGED = 1 << 1,
};
typedef struct wclap_host_mini_curve_display {
   Function<bool, Pointer<const wclap_host>, uint32_t, Pointer<wclap_mini_curve_display_curve_hints>> get_hints;
   Function<void, Pointer<const wclap_host>, bool> set_dynamic;
   Function<void, Pointer<const wclap_host>, uint32_t> changed;
} wclap_host_mini_curve_display;

//---------- ext/draft/project-location.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_PROJECT_LOCATION[] = "clap.project-location/2";
enum wclap_project_location_kind {
   WCLAP_PROJECT_LOCATION_PROJECT = 1,
   WCLAP_PROJECT_LOCATION_TRACK_GROUP = 2,
   WCLAP_PROJECT_LOCATION_TRACK = 3,
   WCLAP_PROJECT_LOCATION_DEVICE = 4,
   WCLAP_PROJECT_LOCATION_NESTED_DEVICE_CHAIN = 5,
};
enum wclap_project_location_track_kind {
   WCLAP_PROJECT_LOCATION_INSTUMENT_TRACK = 1,
   WCLAP_PROJECT_LOCATION_AUDIO_TRACK = 2,
   WCLAP_PROJECT_LOCATION_HYBRID_TRACK = 3,
   WCLAP_PROJECT_LOCATION_RETURN_TRACK = 4,
   WCLAP_PROJECT_LOCATION_MASTER_TRACK = 5,
};
enum wclap_project_location_flags {
   WCLAP_PROJECT_LOCATION_HAS_INDEX = 1 << 0,
   WCLAP_PROJECT_LOCATION_HAS_COLOR = 1 << 1,
};
typedef struct wclap_project_location_element {
   uint64_t flags;
   uint32_t kind;
   uint32_t track_kind;
   uint32_t index;
   char id[WCLAP_PATH_SIZE];
   char name[WCLAP_NAME_SIZE];
   wclap_color color;
} wclap_project_location_element;
typedef struct wclap_plugin_project_location {
   Function<void, Pointer<const wclap_plugin>, Pointer<const wclap_project_location_element>, uint32_t> set;
} wclap_plugin_project_location;

//---------- ext/draft/resource-directory.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_RESOURCE_DIRECTORY[] = "clap.resource-directory/1";
typedef struct wclap_plugin_resource_directory {
   Function<void, Pointer<const wclap_plugin>, Pointer<const char>, bool> set_directory;
   Function<void, Pointer<const wclap_plugin>, bool> collect;
   Function<uint32_t, Pointer<const wclap_plugin>> get_files_count;
   Function<int32_t, Pointer<const wclap_plugin>, uint32_t, Pointer<char>, uint32_t> get_file_path;
} wclap_plugin_resource_directory;
typedef struct wclap_host_resource_directory {
   Function<bool, Pointer<const wclap_host>, bool> request_directory;
   Function<void, Pointer<const wclap_host>, bool> release_directory;
} wclap_host_resource_directory;

//---------- ext/draft/scratch-memory.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_SCRATCH_MEMORY[] = "clap.scratch-memory/1";
typedef struct wclap_host_scratch_memory {
   Function<bool, Pointer<const wclap_host>, uint32_t, uint32_t> reserve;
   Function<Pointer<void>, Pointer<const wclap_host>> access;
} wclap_host_scratch_memory;

//---------- ext/draft/transport-control.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_TRANSPORT_CONTROL[] = "clap.transport-control/1";
typedef struct wclap_host_transport_control {
   Function<void, Pointer<const wclap_host>> request_start;
   Function<void, Pointer<const wclap_host>> request_stop;
   Function<void, Pointer<const wclap_host>> request_continue;
   Function<void, Pointer<const wclap_host>> request_pause;
   Function<void, Pointer<const wclap_host>> request_toggle_play;
   Function<void, Pointer<const wclap_host>, wclap_beattime> request_jump;
   Function<void, Pointer<const wclap_host>, wclap_beattime, wclap_beattime> request_loop_region;
   Function<void, Pointer<const wclap_host>> request_toggle_loop;
   Function<void, Pointer<const wclap_host>, bool> request_enable_loop;
   Function<void, Pointer<const wclap_host>, bool> request_record;
   Function<void, Pointer<const wclap_host>> request_toggle_record;
} wclap_host_transport_control;

//---------- ext/draft/triggers.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_TRIGGERS[] = "clap.triggers/1";
enum {
   WCLAP_TRIGGER_IS_AUTOMATABLE_PER_NOTE_ID = 1 << 0,
   WCLAP_TRIGGER_IS_AUTOMATABLE_PER_KEY = 1 << 1,
   WCLAP_TRIGGER_IS_AUTOMATABLE_PER_CHANNEL = 1 << 2,
   WCLAP_TRIGGER_IS_AUTOMATABLE_PER_PORT = 1 << 3,
};
typedef uint32_t wclap_trigger_info_flags;
enum { WCLAP_EVENT_TRIGGER = 0 };
typedef struct wclap_event_trigger {
   wclap_event_header header;
   wclap_id trigger_id;
   Pointer<void> cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
} wclap_event_trigger;
typedef struct wclap_trigger_info {
   wclap_id id;
   wclap_trigger_info_flags flags;
   Pointer<void> cookie;
   char name[WCLAP_NAME_SIZE];
   char module[WCLAP_PATH_SIZE];
} wclap_trigger_info;
typedef struct wclap_plugin_triggers {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_trigger_info>> get_info;
} wclap_plugin_triggers;
enum {
   WCLAP_TRIGGER_RESCAN_INFO = 1 << 0,
   WCLAP_TRIGGER_RESCAN_ALL = 1 << 1,
};
typedef uint32_t wclap_trigger_rescan_flags;
enum {
   WCLAP_TRIGGER_CLEAR_ALL = 1 << 0,
   WCLAP_TRIGGER_CLEAR_AUTOMATIONS = 1 << 1,
};
typedef uint32_t wclap_trigger_clear_flags;
typedef struct wclap_host_triggers {
   Function<void, Pointer<const wclap_host>, wclap_trigger_rescan_flags> rescan;
   Function<void, Pointer<const wclap_host>, wclap_id, wclap_trigger_clear_flags> clear;
} wclap_host_triggers;

//---------- ext/draft/tuning.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_TUNING[] = "clap.tuning/2";
typedef struct wclap_event_tuning {
   wclap_event_header header;
   int16_t port_index;
   int16_t channel;
   wclap_id tunning_id;
} wclap_event_tuning;
typedef struct wclap_tuning_info {
   wclap_id tuning_id;
   char name[WCLAP_NAME_SIZE];
   bool is_dynamic;
} wclap_tuning_info;
typedef struct wclap_plugin_tuning {
   Function<void, Pointer<const wclap_plugin>> changed;
} wclap_plugin_tuning;
typedef struct wclap_host_tuning {
   Function<double, Pointer<const wclap_host>, wclap_id, int32_t, int32_t, uint32_t> get_relative;
   Function<bool, Pointer<const wclap_host>, wclap_id, int32_t, int32_t> should_play;
   Function<uint32_t, Pointer<const wclap_host>> get_tuning_count;
   Function<bool, Pointer<const wclap_host>, uint32_t, Pointer<wclap_tuning_info>> get_info;
} wclap_host_tuning;

//---------- ext/draft/undo.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_UNDO[] = "clap.undo/4";
static WCLAP_CONSTEXPR const char WCLAP_EXT_UNDO_CONTEXT[] = "clap.undo_context/4";
static WCLAP_CONSTEXPR const char WCLAP_EXT_UNDO_DELTA[] = "clap.undo_delta/4";
typedef struct wclap_undo_delta_properties {
   bool has_delta;
   bool are_deltas_persistent;
   wclap_id format_version;
} wclap_undo_delta_properties;
typedef struct wclap_plugin_undo_delta {
   Function<void, Pointer<const wclap_plugin>, Pointer<wclap_undo_delta_properties>> get_delta_properties;
   Function<bool, Pointer<const wclap_plugin>, wclap_id> can_use_delta_format_version;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, Pointer<const void>, size_t> undo;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, Pointer<const void>, size_t> redo;
} wclap_plugin_undo_delta;
typedef struct wclap_plugin_undo_context {
   Function<void, Pointer<const wclap_plugin>, bool> set_can_undo;
   Function<void, Pointer<const wclap_plugin>, bool> set_can_redo;
   Function<void, Pointer<const wclap_plugin>, Pointer<const char>> set_undo_name;
   Function<void, Pointer<const wclap_plugin>, Pointer<const char>> set_redo_name;
} wclap_plugin_undo_context;
typedef struct wclap_host_undo {
   Function<void, Pointer<const wclap_host>> begin_change;
   Function<void, Pointer<const wclap_host>> cancel_change;
   Function<void, Pointer<const wclap_host>, Pointer<const char>, Pointer<const void>, size_t, bool> change_made;
   Function<void, Pointer<const wclap_host>> request_undo;
   Function<void, Pointer<const wclap_host>> request_redo;
   Function<void, Pointer<const wclap_host>, bool> set_wants_context_updates;
} wclap_host_undo;

//---------- ext/draft/webview.h

static WCLAP_CONSTEXPR const char WCLAP_EXT_WEBVIEW[] = "clap.webview/3";
static const WCLAP_CONSTEXPR char WCLAP_WINDOW_API_WEBVIEW[] = "webview";
typedef struct wclap_plugin_webview {
   Function<int32_t, Pointer<const wclap_plugin>, Pointer<char>, uint32_t> get_uri;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const char>, Pointer<char>, uint32_t, Pointer<const wclap_ostream>> get_resource;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const void>, uint32_t> receive;
} wclap_plugin_webview;
typedef struct wclap_host_webview {
   Function<bool, Pointer<const wclap_host>, Pointer<const void>, uint32_t> send;
} wclap_host_webview;

//---------- all.h


