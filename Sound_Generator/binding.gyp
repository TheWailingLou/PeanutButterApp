{
    "targets":[
        {
            "target_name": "peanutButter",
            "sources": [
                "main.cc",
                "./arrangement/arrangement_main.cc",
                "./arrangement/arrangement_all.cc",
                "./arrangement/drum_arrangement.cc",
                "./arrangement/key_and_chord_arrangement.cc",
                "./arrangement/bass_arrangement.cc",

                "./generators/drums/hi_hat_generator.cc",
                "./generators/drums/kick_generator.cc",
                "./generators/drums/snare_generator.cc",
                "./generators/drums/tom_generator.cc",

                "./generators/bass/bass_main.cc",
                "./generators/chords/chord_gen.cc",

                "./generators/music_gen.cc",

                "./js_io/drum_imports.cc",
                "./js_io/get_buffers.cc",

                "./readers/drums/crash_writer.cc",
                "./readers/drums/hi_hat_writer.cc",
                "./readers/drums/kick_writer.cc",
                "./readers/drums/snare_writer.cc",
                "./readers/drums/tom_writer.cc",

                "./readers/bass/bass_voice.cc",
                "./readers/bass/bass_writer.cc",

                "./setup_and_help/audio_helper.cc",
                "./setup_and_help/audio_setup.cc",
                "./setup_and_help/scales.cc",
                "./setup_and_help/notes.cc",
                "./setup_and_help/tones.cc",

                "./tracks/drum_track.cc",
                "./tracks/bass_track.cc"
            ]
        }
    ]
}
