
/* Generated code - do not edit by hand.

This includes all the CLAP API typedefs and structs, but:
	* renamed clap_ -> wclap_
	* T * replaced by Pointer<T>
	* function pointers replaced by Function<Return, Args...>

You should be able to include this inside another namespace, as long as Function<> and Pointer<> are defined.  These must be simple wrappers around integers, and have the same size as pointers inside the WASM module.
*/

struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_plugin_entry {
   wclap_version wclap_version;
   Function<bool, Pointer<const char>> init;
   Function<void> deinit;
   Function<Pointer<const void>, Pointer<const char>> get_factory;
};
struct wclap_host {
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
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header header;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double velocity;
};
struct wclap_event_note_expression {
   wclap_event_header header;
   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double value;
};
struct wclap_event_param_value {
   wclap_event_header header;
   wclap_id param_id;
   Pointer<void> cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double value;
};
struct wclap_event_param_mod {
   wclap_event_header header;
   wclap_id param_id;
   Pointer<void> cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header header;
   wclap_id param_id;
};
struct wclap_event_transport {
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
};
struct wclap_event_midi {
   wclap_event_header header;
   uint16_t port_index;
   uint8_t data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header header;
   uint16_t port_index;
   Pointer<const uint8_t> buffer;
   uint32_t size;
};
struct wclap_event_midi2 {
   wclap_event_header header;
   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t, Pointer<const struct wclap_input_events>> size;
   Function<Pointer<const wclap_event_header>, Pointer<const struct wclap_input_events>, uint32_t> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool, Pointer<const struct wclap_output_events>, Pointer<const wclap_event_header>> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>> data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport> transport;
   Pointer<const wclap_audio_buffer> audio_inputs;
   Pointer<wclap_audio_buffer> audio_outputs;
   uint32_t audio_inputs_count;
   uint32_t audio_outputs_count;
   Pointer<const wclap_input_events> in_events;
   Pointer<const wclap_output_events> out_events;
};
struct wclap_plugin_descriptor {
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
};
struct wclap_plugin {
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
};
struct wclap_plugin_factory {
   Function<uint32_t, Pointer<const struct wclap_plugin_factory>> get_plugin_count;
   Function<Pointer<const wclap_plugin_descriptor>, Pointer<const struct wclap_plugin_factory>, uint32_t> get_plugin_descriptor;
   Function<Pointer<const wclap_plugin>, Pointer<const struct wclap_plugin_factory>, Pointer<const wclap_host>, Pointer<const char>> create_plugin;
};
typedef uint64_t wclap_timestamp;
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_preset_discovery_metadata_receiver {
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
};
struct wclap_preset_discovery_filetype {
   Pointer<const char> name;
   Pointer<const char> description;
   Pointer<const char> file_extension;
};
struct wclap_preset_discovery_location {
   uint32_t flags;
   Pointer<const char> name;
   uint32_t kind;
   Pointer<const char> location;
};
struct wclap_preset_discovery_soundpack {
   uint32_t flags;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> description;
   Pointer<const char> homepage_url;
   Pointer<const char> vendor;
   Pointer<const char> image_path;
   wclap_timestamp release_timestamp;
};
struct wclap_preset_discovery_provider_descriptor {
   wclap_version wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
};
struct wclap_preset_discovery_provider {
   Pointer<const wclap_preset_discovery_provider_descriptor> desc;
   Pointer<void> provider_data;
   Function<bool, Pointer<const struct wclap_preset_discovery_provider>> init;
   Function<void, Pointer<const struct wclap_preset_discovery_provider>> destroy;
   Function<bool, Pointer<const struct wclap_preset_discovery_provider>, uint32_t, Pointer<const char>, Pointer<const wclap_preset_discovery_metadata_receiver>> get_metadata;
   Function<Pointer<const void>, Pointer<const struct wclap_preset_discovery_provider>, Pointer<const char>> get_extension;
};
struct wclap_preset_discovery_indexer {
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
};
struct wclap_preset_discovery_factory {
   Function<uint32_t, Pointer<const struct wclap_preset_discovery_factory>> count;
   Function<Pointer<const wclap_preset_discovery_provider_descriptor>, Pointer<const struct wclap_preset_discovery_factory>, uint32_t> get_descriptor;
   Function<Pointer<const wclap_preset_discovery_provider>, Pointer<const struct wclap_preset_discovery_factory>, Pointer<const wclap_preset_discovery_indexer>, Pointer<const char>> create;
};
struct wclap_ambisonic_config {
   uint32_t ordering;
   uint32_t normalization;
};
struct wclap_plugin_ambisonic {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_ambisonic_config>> is_config_supported;
   Function<bool, Pointer<const wclap_plugin>, bool, uint32_t, Pointer<wclap_ambisonic_config>> get_config;
};
struct wclap_host_ambisonic {
   Function<void, Pointer<const wclap_host>> changed;
};
struct wclap_plugin_audio_ports_activation {
   Function<bool, Pointer<const wclap_plugin>> can_activate_while_processing;
   Function<bool, Pointer<const wclap_plugin>, bool, uint32_t, bool, uint32_t> set_active;
};
struct wclap_audio_port_info {
   wclap_id id;
   char name[256];
   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t, Pointer<const wclap_plugin>, bool> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, bool, Pointer<wclap_audio_port_info>> get;
};
struct wclap_host_audio_ports {
   Function<bool, Pointer<const wclap_host>, uint32_t> is_rescan_flag_supported;
   Function<void, Pointer<const wclap_host>, uint32_t> rescan;
};
struct wclap_audio_ports_config {
   wclap_id id;
   char name[256];
   uint32_t input_port_count;
   uint32_t output_port_count;
   bool has_main_input;
   uint32_t main_input_channel_count;
   Pointer<const char> main_input_port_type;
   bool has_main_output;
   uint32_t main_output_channel_count;
   Pointer<const char> main_output_port_type;
};
struct wclap_plugin_audio_ports_config {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_audio_ports_config>> get;
   Function<bool, Pointer<const wclap_plugin>, wclap_id> select;
};
struct wclap_plugin_audio_ports_config_info {
   Function<wclap_id, Pointer<const wclap_plugin>> current_config;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, uint32_t, bool, Pointer<wclap_audio_port_info>> get;
};
struct wclap_host_audio_ports_config {
   Function<void, Pointer<const wclap_host>> rescan;
};
struct wclap_audio_port_configuration_request {
   bool is_input;
   uint32_t port_index;
   uint32_t channel_count;
   Pointer<const char> port_type;
   Pointer<const void> port_details;
};
struct wclap_plugin_configurable_audio_ports {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const struct wclap_audio_port_configuration_request>, uint32_t> can_apply_configuration;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const struct wclap_audio_port_configuration_request>, uint32_t> apply_configuration;
};
typedef uint32_t wclap_context_menu_item_kind;
struct wclap_context_menu_target {
   uint32_t kind;
   wclap_id id;
};
struct wclap_context_menu_entry {
   Pointer<const char> label;
   bool is_enabled;
   wclap_id action_id;
};
struct wclap_context_menu_check_entry {
   Pointer<const char> label;
   bool is_enabled;
   bool is_checked;
   wclap_id action_id;
};
struct wclap_context_menu_item_title {
   Pointer<const char> title;
   bool is_enabled;
};
struct wclap_context_menu_submenu {
   Pointer<const char> label;
   bool is_enabled;
};
struct wclap_context_menu_builder {
   Pointer<void> ctx;
   Function<bool, Pointer<const struct wclap_context_menu_builder>, wclap_context_menu_item_kind, Pointer<const void>> add_item;
   Function<bool, Pointer<const struct wclap_context_menu_builder>, wclap_context_menu_item_kind> supports;
};
struct wclap_plugin_context_menu {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_context_menu_target>, Pointer<const wclap_context_menu_builder>> populate;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_context_menu_target>, wclap_id> perform;
};
struct wclap_host_context_menu {
   Function<bool, Pointer<const wclap_host>, Pointer<const wclap_context_menu_target>, Pointer<const wclap_context_menu_builder>> populate;
   Function<bool, Pointer<const wclap_host>, Pointer<const wclap_context_menu_target>, wclap_id> perform;
   Function<bool, Pointer<const wclap_host>> can_popup;
   Function<bool, Pointer<const wclap_host>, Pointer<const wclap_context_menu_target>, int32_t, int32_t, int32_t> popup;
};
struct wclap_host_event_registry {
   Function<bool, Pointer<const wclap_host>, Pointer<const char>, Pointer<uint16_t>> query;
};
typedef Pointer<void> wclap_hwnd;
typedef Pointer<void> wclap_nsview;
typedef unsigned long wclap_xwnd;
struct wclap_window {
   Pointer<const char> api;
   union {
      wclap_nsview cocoa;
      wclap_xwnd x11;
      wclap_hwnd win32;
      Pointer<void> ptr;
   };
};
struct wclap_gui_resize_hints {
   bool can_resize_horizontally;
   bool can_resize_vertically;
   bool preserve_aspect_ratio;
   uint32_t aspect_ratio_width;
   uint32_t aspect_ratio_height;
};
struct wclap_plugin_gui {
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
};
struct wclap_host_gui {
   Function<void, Pointer<const wclap_host>> resize_hints_changed;
   Function<bool, Pointer<const wclap_host>, uint32_t, uint32_t> request_resize;
   Function<bool, Pointer<const wclap_host>> request_show;
   Function<bool, Pointer<const wclap_host>> request_hide;
   Function<void, Pointer<const wclap_host>, bool> closed;
};
struct wclap_plugin_latency {
   Function<uint32_t, Pointer<const wclap_plugin>> get;
};
struct wclap_host_latency {
   Function<void, Pointer<const wclap_host>> changed;
};
typedef int32_t wclap_log_severity;
struct wclap_host_log {
   Function<void, Pointer<const wclap_host>, wclap_log_severity, Pointer<const char>> log;
};
struct wclap_note_name {
   char name[256];
   int16_t port;
   int16_t key;
   int16_t channel;
};
struct wclap_plugin_note_name {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_note_name>> get;
};
struct wclap_host_note_name {
   Function<void, Pointer<const wclap_host>> changed;
};
struct wclap_note_port_info {
   wclap_id id;
   uint32_t supported_dialects;
   uint32_t preferred_dialect;
   char name[256];
};
struct wclap_plugin_note_ports {
   Function<uint32_t, Pointer<const wclap_plugin>, bool> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, bool, Pointer<wclap_note_port_info>> get;
};
struct wclap_host_note_ports {
   Function<uint32_t, Pointer<const wclap_host>> supported_dialects;
   Function<void, Pointer<const wclap_host>, uint32_t> rescan;
};
typedef uint32_t wclap_param_info_flags;
typedef uint32_t wclap_param_rescan_flags;
typedef uint32_t wclap_param_clear_flags;
struct wclap_param_info {
   wclap_id id;
   wclap_param_info_flags flags;
   Pointer<void> cookie;
   char name[256];
   char module[1024];
   double min_value;
   double max_value;
   double default_value;
};
struct wclap_plugin_params {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_param_info>> get_info;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, Pointer<double>> get_value;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, double, Pointer<char>, uint32_t> value_to_text;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, Pointer<const char>, Pointer<double>> text_to_value;
   Function<void, Pointer<const wclap_plugin>, Pointer<const wclap_input_events>, Pointer<const wclap_output_events>> flush;
};
struct wclap_host_params {
   Function<void, Pointer<const wclap_host>, wclap_param_rescan_flags> rescan;
   Function<void, Pointer<const wclap_host>, wclap_id, wclap_param_clear_flags> clear;
   Function<void, Pointer<const wclap_host>> request_flush;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_plugin_param_indication {
   Function<void, Pointer<const wclap_plugin>, wclap_id, bool, Pointer<const wclap_color>, Pointer<const char>, Pointer<const char>> set_mapping;
   Function<void, Pointer<const wclap_plugin>, wclap_id, uint32_t, Pointer<const wclap_color>> set_automation;
};
typedef uint32_t wclap_posix_fd_flags;
struct wclap_plugin_posix_fd_support {
   Function<void, Pointer<const wclap_plugin>, int, wclap_posix_fd_flags> on_fd;
};
struct wclap_host_posix_fd_support {
   Function<bool, Pointer<const wclap_host>, int, wclap_posix_fd_flags> register_fd;
   Function<bool, Pointer<const wclap_host>, int, wclap_posix_fd_flags> modify_fd;
   Function<bool, Pointer<const wclap_host>, int> unregister_fd;
};
struct wclap_plugin_preset_load {
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<const char>, Pointer<const char>> from_location;
};
struct wclap_host_preset_load {
   Function<void, Pointer<const wclap_host>, uint32_t, Pointer<const char>, Pointer<const char>, int32_t, Pointer<const char>> on_error;
   Function<void, Pointer<const wclap_host>, uint32_t, Pointer<const char>, Pointer<const char>> loaded;
};
struct wclap_remote_controls_page {
   char section_name[256];
   wclap_id page_id;
   char page_name[256];
   wclap_id param_ids[8];
   bool is_for_preset;
};
struct wclap_plugin_remote_controls {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_remote_controls_page>> get;
};
struct wclap_host_remote_controls {
   Function<void, Pointer<const wclap_host>> changed;
   Function<void, Pointer<const wclap_host>, wclap_id> suggest_page;
};
typedef int32_t wclap_plugin_render_mode;
struct wclap_plugin_render {
   Function<bool, Pointer<const wclap_plugin>> has_hard_realtime_requirement;
   Function<bool, Pointer<const wclap_plugin>, wclap_plugin_render_mode> set;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t, Pointer<const struct wclap_istream>, Pointer<void>, uint64_t> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t, Pointer<const struct wclap_ostream>, Pointer<const void>, uint64_t> write;
};
struct wclap_plugin_state_context {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_ostream>, uint32_t> save;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_istream>, uint32_t> load;
};
struct wclap_plugin_state {
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_ostream>> save;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const wclap_istream>> load;
};
struct wclap_host_state {
   Function<void, Pointer<const wclap_host>> mark_dirty;
};
struct wclap_plugin_surround {
   Function<bool, Pointer<const wclap_plugin>, uint64_t> is_channel_mask_supported;
   Function<uint32_t, Pointer<const wclap_plugin>, bool, uint32_t, Pointer<uint8_t>, uint32_t> get_channel_map;
};
struct wclap_host_surround {
   Function<void, Pointer<const wclap_host>> changed;
};
struct wclap_plugin_tail {
   Function<uint32_t, Pointer<const wclap_plugin>> get;
};
struct wclap_host_tail {
   Function<void, Pointer<const wclap_host>> changed;
};
struct wclap_host_thread_check {
   Function<bool, Pointer<const wclap_host>> is_main_thread;
   Function<bool, Pointer<const wclap_host>> is_audio_thread;
};
struct wclap_plugin_thread_pool {
   Function<void, Pointer<const wclap_plugin>, uint32_t> exec;
};
struct wclap_host_thread_pool {
   Function<bool, Pointer<const wclap_host>, uint32_t> request_exec;
};
struct wclap_plugin_timer_support {
   Function<void, Pointer<const wclap_plugin>, wclap_id> on_timer;
};
struct wclap_host_timer_support {
   Function<bool, Pointer<const wclap_host>, uint32_t, Pointer<wclap_id>> register_timer;
   Function<bool, Pointer<const wclap_host>, wclap_id> unregister_timer;
};
struct wclap_track_info {
   uint64_t flags;
   char name[256];
   wclap_color color;
   int32_t audio_channel_count;
   Pointer<const char> audio_port_type;
};
struct wclap_plugin_track_info {
   Function<void, Pointer<const wclap_plugin>> changed;
};
struct wclap_host_track_info {
   Function<bool, Pointer<const wclap_host>, Pointer<wclap_track_info>> get;
};
struct wclap_voice_info {
   uint32_t voice_count;
   uint32_t voice_capacity;
   uint64_t flags;
};
struct wclap_plugin_voice_info {
   Function<bool, Pointer<const wclap_plugin>, Pointer<wclap_voice_info>> get;
};
struct wclap_host_voice_info {
   Function<void, Pointer<const wclap_host>> changed;
};
struct wclap_plugin_invalidation_source {
   Pointer<const char> directory;
   Pointer<const char> filename_glob;
   bool recursive_scan;
};
struct wclap_plugin_invalidation_factory {
   Function<uint32_t, Pointer<const struct wclap_plugin_invalidation_factory>> count;
   Function<Pointer<const wclap_plugin_invalidation_source>, Pointer<const struct wclap_plugin_invalidation_factory>, uint32_t> get;
   Function<bool, Pointer<const struct wclap_plugin_invalidation_factory>> refresh;
};
struct wclap_plugin_state_converter_descriptor {
   wclap_version wclap_version;
   wclap_universal_plugin_id src_plugin_id;
   wclap_universal_plugin_id dst_plugin_id;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> version;
   Pointer<const char> description;
};
struct wclap_plugin_state_converter {
   Pointer<const wclap_plugin_state_converter_descriptor> desc;
   Pointer<void> converter_data;
   Function<void, Pointer<struct wclap_plugin_state_converter>> destroy;
   Function<bool, Pointer<struct wclap_plugin_state_converter>, Pointer<const wclap_istream>, Pointer<const wclap_ostream>, Pointer<char>, size_t> convert_state;
   Function<bool, Pointer<struct wclap_plugin_state_converter>, wclap_id, double, Pointer<wclap_id>, Pointer<double>> convert_normalized_value;
   Function<bool, Pointer<struct wclap_plugin_state_converter>, wclap_id, double, Pointer<wclap_id>, Pointer<double>> convert_plain_value;
};
struct wclap_plugin_state_converter_factory {
   Function<uint32_t, Pointer<const struct wclap_plugin_state_converter_factory>> count;
   Function<Pointer<const wclap_plugin_state_converter_descriptor>, Pointer<const struct wclap_plugin_state_converter_factory>, uint32_t> get_descriptor;
   Function<Pointer<wclap_plugin_state_converter>, Pointer<const struct wclap_plugin_state_converter_factory>, Pointer<const char>> create;
};
struct wclap_plugin_extensible_audio_ports {
   Function<bool, Pointer<const wclap_plugin>, bool, uint32_t, Pointer<const char>, Pointer<const void>> add_port;
   Function<bool, Pointer<const wclap_plugin>, bool, uint32_t> remove_port;
};
struct wclap_plugin_gain_adjustment_metering {
  Function<double, Pointer<const wclap_plugin>> get;
};
struct wclap_mini_curve_display_curve_hints {
   double x_min;
   double x_max;
   double y_min;
   double y_max;
};
struct wclap_mini_curve_display_curve_data {
   int32_t curve_kind;
   Pointer<uint16_t> values;
   uint32_t values_count;
};
struct wclap_plugin_mini_curve_display {
   Function<uint32_t, Pointer<const wclap_plugin>> get_curve_count;
   Function<uint32_t, Pointer<const wclap_plugin>, Pointer<wclap_mini_curve_display_curve_data>, uint32_t> render;
   Function<void, Pointer<const wclap_plugin>, bool> set_observed;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<char>, Pointer<char>, uint32_t> get_axis_name;
};
struct wclap_host_mini_curve_display {
   Function<bool, Pointer<const wclap_host>, uint32_t, Pointer<wclap_mini_curve_display_curve_hints>> get_hints;
   Function<void, Pointer<const wclap_host>, bool> set_dynamic;
   Function<void, Pointer<const wclap_host>, uint32_t> changed;
};
struct wclap_project_location_element {
   uint64_t flags;
   uint32_t kind;
   uint32_t track_kind;
   uint32_t index;
   char id[1024];
   char name[256];
   wclap_color color;
};
struct wclap_plugin_project_location {
   Function<void, Pointer<const wclap_plugin>, Pointer<const wclap_project_location_element>, uint32_t> set;
};
struct wclap_plugin_resource_directory {
   Function<void, Pointer<const wclap_plugin>, Pointer<const char>, bool> set_directory;
   Function<void, Pointer<const wclap_plugin>, bool> collect;
   Function<uint32_t, Pointer<const wclap_plugin>> get_files_count;
   Function<int32_t, Pointer<const wclap_plugin>, uint32_t, Pointer<char>, uint32_t> get_file_path;
};
struct wclap_host_resource_directory {
   Function<bool, Pointer<const wclap_host>, bool> request_directory;
   Function<void, Pointer<const wclap_host>, bool> release_directory;
};
struct wclap_host_scratch_memory {
   Function<bool, Pointer<const wclap_host>, uint32_t, uint32_t> reserve;
   Function<Pointer<void>, Pointer<const wclap_host>> access;
};
struct wclap_host_transport_control {
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
};
typedef uint32_t wclap_trigger_info_flags;
typedef uint32_t wclap_trigger_rescan_flags;
typedef uint32_t wclap_trigger_clear_flags;
struct wclap_event_trigger {
   wclap_event_header header;
   wclap_id trigger_id;
   Pointer<void> cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
};
struct wclap_trigger_info {
   wclap_id id;
   wclap_trigger_info_flags flags;
   Pointer<void> cookie;
   char name[256];
   char module[1024];
};
struct wclap_plugin_triggers {
   Function<uint32_t, Pointer<const wclap_plugin>> count;
   Function<bool, Pointer<const wclap_plugin>, uint32_t, Pointer<wclap_trigger_info>> get_info;
};
struct wclap_host_triggers {
   Function<void, Pointer<const wclap_host>, wclap_trigger_rescan_flags> rescan;
   Function<void, Pointer<const wclap_host>, wclap_id, wclap_trigger_clear_flags> clear;
};
struct wclap_event_tuning {
   wclap_event_header header;
   int16_t port_index;
   int16_t channel;
   wclap_id tunning_id;
};
struct wclap_tuning_info {
   wclap_id tuning_id;
   char name[256];
   bool is_dynamic;
};
struct wclap_plugin_tuning {
   Function<void, Pointer<const wclap_plugin>> changed;
};
struct wclap_host_tuning {
   Function<double, Pointer<const wclap_host>, wclap_id, int32_t, int32_t, uint32_t> get_relative;
   Function<bool, Pointer<const wclap_host>, wclap_id, int32_t, int32_t> should_play;
   Function<uint32_t, Pointer<const wclap_host>> get_tuning_count;
   Function<bool, Pointer<const wclap_host>, uint32_t, Pointer<wclap_tuning_info>> get_info;
};
struct wclap_undo_delta_properties {
   bool has_delta;
   bool are_deltas_persistent;
   wclap_id format_version;
};
struct wclap_plugin_undo_delta {
   Function<void, Pointer<const wclap_plugin>, Pointer<wclap_undo_delta_properties>> get_delta_properties;
   Function<bool, Pointer<const wclap_plugin>, wclap_id> can_use_delta_format_version;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, Pointer<const void>, size_t> undo;
   Function<bool, Pointer<const wclap_plugin>, wclap_id, Pointer<const void>, size_t> redo;
};
struct wclap_plugin_undo_context {
   Function<void, Pointer<const wclap_plugin>, bool> set_can_undo;
   Function<void, Pointer<const wclap_plugin>, bool> set_can_redo;
   Function<void, Pointer<const wclap_plugin>, Pointer<const char>> set_undo_name;
   Function<void, Pointer<const wclap_plugin>, Pointer<const char>> set_redo_name;
};
struct wclap_host_undo {
   Function<void, Pointer<const wclap_host>> begin_change;
   Function<void, Pointer<const wclap_host>> cancel_change;
   Function<void, Pointer<const wclap_host>, Pointer<const char>, Pointer<const void>, size_t, bool> change_made;
   Function<void, Pointer<const wclap_host>> request_undo;
   Function<void, Pointer<const wclap_host>> request_redo;
   Function<void, Pointer<const wclap_host>, bool> set_wants_context_updates;
};
struct wclap_plugin_webview {
   Function<int32_t, Pointer<const wclap_plugin>, Pointer<char>, uint32_t> get_uri;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const char>, Pointer<char>, uint32_t, Pointer<const wclap_ostream>> get_resource;
   Function<bool, Pointer<const wclap_plugin>, Pointer<const void>, uint32_t> receive;
};
struct wclap_host_webview {
   Function<bool, Pointer<const wclap_host>, Pointer<const void>, uint32_t> send;
};
