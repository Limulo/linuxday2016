s.meter;
(
SynthDef.new(\pm,{
	arg midi=60, tone=3, art=1, amp=0.8, pan=0;
	var env, out, mod, freq;

	freq = midi.midicps;
	env = Env.perc([0, 0.05, 0.1, 0.025], art, LFNoise0.kr([1, 1.25]).range(0.1, 1), -1);
	mod = SinOsc.kr([0.2, 0.4, 0.1, 0.6], mul:0.5, add:1)*3 + (1/IRand(2, 6));
	//mod = 5 + (1/IRand(2,6));
	out = PMOsc.ar(
		[freq, freq/2, freq*1/3, freq*2/3],
		mod*freq,
		modphase: [0, 0.1, 0.25, 0.5],
		pmindex: EnvGen.kr(env, timeScale: art, levelScale: tone),
		mul: EnvGen.kr(env, timeScale: [art, art*1/IRand(2, 4)], levelScale: 0.3));
	out = out * EnvGen.kr(env, timeScale: 1.3*art, levelScale: Rand(0.1, 0.5), doneAction:2);
	out = Splay.ar(out);
	Out.ar(0, out)

}).add;
)

(

a = ["C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B"];
"event, midi, pitch, octave".postln;
t = Task({
	inf.do({arg count;
		var midi, octave, density;
		//density = [1.0, 0.7, 0.3].choose;
		density = 1;
		midi = [0, 2, 4, 7].choose;
		//midi = [0, 2, 4, 5, 7, 9, 11].choose;
		//midi = [0, 2, 3, 5, 6, 8, 9, 11].choose;
		//midi = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11].choose;
		octave = [32, 48, 60, 54, 72].choose;
		if(density.coin,
			{
				"".postln;
				[midi + octave, a.wrapAt(midi), (octave/12).round(1)].post;
				Synth(\pm, [\midi, midi + octave, \tone, rrand(1, 7), \art, rrand(0.8, 2.0), \amp, rrand(0.3, 0.6), \pan, 1.0.rand2]);
			},
			{"pausa".postln}
		);
		0.2.wait;
	})

}).start;
)
t.stop;