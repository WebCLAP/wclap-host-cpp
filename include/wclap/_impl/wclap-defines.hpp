//---------- version.h
#define WCLAP_VERSION_MAJOR 1
#define WCLAP_VERSION_MINOR 2
#define WCLAP_VERSION_REVISION 7
#define WCLAP_VERSION_INIT \
   { (uint32_t)WCLAP_VERSION_MAJOR, (uint32_t)WCLAP_VERSION_MINOR, (uint32_t)WCLAP_VERSION_REVISION }
#define WCLAP_VERSION_LT(maj, min, rev) ((WCLAP_VERSION_MAJOR < (maj)) || \
                    ((maj) == WCLAP_VERSION_MAJOR && WCLAP_VERSION_MINOR < (min)) || \
                    ((maj) == WCLAP_VERSION_MAJOR && (min) == WCLAP_VERSION_MINOR && WCLAP_VERSION_REVISION < (rev)))
#define WCLAP_VERSION_EQ(maj, min, rev) (((maj) == WCLAP_VERSION_MAJOR) && ((min) == WCLAP_VERSION_MINOR) && ((rev) == WCLAP_VERSION_REVISION))
#define WCLAP_VERSION_GE(maj, min, rev) (!WCLAP_VERSION_LT(maj, min, rev))
//---------- entry.h
//---------- host.h
//---------- fixedpoint.h
//---------- id.h
//---------- events.h
//---------- audio-buffer.h
//---------- process.h
//---------- plugin-features.h
#define WCLAP_PLUGIN_FEATURE_INSTRUMENT "instrument"
#define WCLAP_PLUGIN_FEATURE_AUDIO_EFFECT "audio-effect"
#define WCLAP_PLUGIN_FEATURE_NOTE_EFFECT "note-effect"
#define WCLAP_PLUGIN_FEATURE_NOTE_DETECTOR "note-detector"
#define WCLAP_PLUGIN_FEATURE_ANALYZER "analyzer"
#define WCLAP_PLUGIN_FEATURE_SYNTHESIZER "synthesizer"
#define WCLAP_PLUGIN_FEATURE_SAMPLER "sampler"
#define WCLAP_PLUGIN_FEATURE_DRUM "drum"
#define WCLAP_PLUGIN_FEATURE_DRUM_MACHINE "drum-machine"
#define WCLAP_PLUGIN_FEATURE_FILTER "filter"
#define WCLAP_PLUGIN_FEATURE_PHASER "phaser"
#define WCLAP_PLUGIN_FEATURE_EQUALIZER "equalizer"
#define WCLAP_PLUGIN_FEATURE_DEESSER "de-esser"
#define WCLAP_PLUGIN_FEATURE_PHASE_VOCODER "phase-vocoder"
#define WCLAP_PLUGIN_FEATURE_GRANULAR "granular"
#define WCLAP_PLUGIN_FEATURE_FREQUENCY_SHIFTER "frequency-shifter"
#define WCLAP_PLUGIN_FEATURE_PITCH_SHIFTER "pitch-shifter"
#define WCLAP_PLUGIN_FEATURE_DISTORTION "distortion"
#define WCLAP_PLUGIN_FEATURE_TRANSIENT_SHAPER "transient-shaper"
#define WCLAP_PLUGIN_FEATURE_COMPRESSOR "compressor"
#define WCLAP_PLUGIN_FEATURE_EXPANDER "expander"
#define WCLAP_PLUGIN_FEATURE_GATE "gate"
#define WCLAP_PLUGIN_FEATURE_LIMITER "limiter"
#define WCLAP_PLUGIN_FEATURE_FLANGER "flanger"
#define WCLAP_PLUGIN_FEATURE_CHORUS "chorus"
#define WCLAP_PLUGIN_FEATURE_DELAY "delay"
#define WCLAP_PLUGIN_FEATURE_REVERB "reverb"
#define WCLAP_PLUGIN_FEATURE_TREMOLO "tremolo"
#define WCLAP_PLUGIN_FEATURE_GLITCH "glitch"
#define WCLAP_PLUGIN_FEATURE_UTILITY "utility"
#define WCLAP_PLUGIN_FEATURE_PITCH_CORRECTION "pitch-correction"
#define WCLAP_PLUGIN_FEATURE_RESTORATION "restoration"
#define WCLAP_PLUGIN_FEATURE_MULTI_EFFECTS "multi-effects"
#define WCLAP_PLUGIN_FEATURE_MIXING "mixing"
#define WCLAP_PLUGIN_FEATURE_MASTERING "mastering"
#define WCLAP_PLUGIN_FEATURE_MONO "mono"
#define WCLAP_PLUGIN_FEATURE_STEREO "stereo"
#define WCLAP_PLUGIN_FEATURE_SURROUND "surround"
#define WCLAP_PLUGIN_FEATURE_AMBISONIC "ambisonic"
//---------- plugin.h
//---------- factory/plugin-factory.h
//---------- timestamp.h
//---------- universal-plugin-id.h
//---------- factory/preset-discovery.h
//---------- ext/ambisonic.h
//---------- ext/audio-ports-activation.h
//---------- string-sizes.h
//---------- ext/audio-ports.h
//---------- ext/audio-ports-config.h
//---------- ext/configurable-audio-ports.h
//---------- ext/context-menu.h
//---------- ext/event-registry.h
//---------- ext/gui.h
//---------- ext/latency.h
//---------- ext/log.h
//---------- ext/note-name.h
//---------- ext/note-ports.h
//---------- ext/params.h
//---------- color.h
//---------- ext/param-indication.h
//---------- ext/posix-fd-support.h
//---------- ext/preset-load.h
//---------- ext/remote-controls.h
//---------- ext/render.h
//---------- stream.h
//---------- ext/state-context.h
//---------- ext/state.h
//---------- ext/surround.h
//---------- ext/tail.h
//---------- ext/thread-check.h
//---------- ext/thread-pool.h
//---------- ext/timer-support.h
//---------- ext/track-info.h
//---------- ext/voice-info.h
//---------- clap.h
//---------- factory/draft/plugin-invalidation.h
//---------- factory/draft/plugin-state-converter.h
//---------- ext/draft/extensible-audio-ports.h
//---------- ext/draft/gain-adjustment-metering.h
//---------- ext/draft/mini-curve-display.h
//---------- ext/draft/project-location.h
//---------- ext/draft/resource-directory.h
//---------- ext/draft/scratch-memory.h
//---------- ext/draft/transport-control.h
//---------- ext/draft/triggers.h
//---------- ext/draft/tuning.h
//---------- ext/draft/undo.h
//---------- ext/draft/webview.h
//---------- all.h
