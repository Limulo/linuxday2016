(
SynthDef.new(\space, {
	arg t_gate = 0, amp = 1, maxDelTime = 1, delTime= 0.3, decTime = 2, noiseFreq=3, noiseMul=24, sawFreqL=5, sawFreqR= 5.123, sawMul=3, sawAdd=80, sawPhaseL=0, sawPhaseR=0.125;
	var freq, sig, env;
	freq = midicps(
		LFNoise1.ar(
			freq: noiseFreq,
			mul: noiseMul,
			add: LFSaw.ar(
				freq: [sawFreqL, sawFreqR],
				iphase: [sawPhaseL, sawPhaseR],
				mul: sawMul,
				add: sawAdd)));
	env = EnvGen.kr(Env.perc(0.1, 2, curve:-3), t_gate);
	sig = SinOsc.ar(freq, 0, 0.4);
	sig = CombN.ar(sig, 1, 0.3, 2);
	//DetectSilence.ar(sig, 0.01, 0.1, doneAction:2);
	Out.ar(0, sig*amp*env);
}).add;
)

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
SynthDef.new(\ele3,
	{

	arg midi = 60, phase= 10, duty = 0.125, amp=0.8, t_gate=0;
	var sig, env;
	sig = VarSaw.ar(midi.midicps!16, phase, duty);
	env = EnvGen.kr(Env.new([0, 0.5, 0.8, 0.2, 0],[0.1, 0.1, 0.2, 0.5],[\sine, 2, -2, -2]), t_gate);
	amp = amp - ((midi-60) *0.02);
	sig = Splay.ar(sig);
	Out.ar(0, sig*env*amp)
}).add;
)

(
SynthDef.new(\ele4,
	{
		arg amp, phase=0, t_gate=0, mod=60, freq = 0;
		var sig, env, f1, f2, f3, f4, f5;

		//fund = fund+60.midicps;
		f1 = freq+mod;
		f2 = freq * 3/4 + mod;
		f3 = freq *2 + mod;
		f4 = freq *1/2 + mod;
		f5 = freq *4/3 + mod;
		f1 = f1.midicps * LFNoise0.kr(SinOsc.kr(12).range(0.1, 1));
		f2 = f2.midicps * LFNoise0.kr(SinOsc.kr(12).range(0.1, 1));
		f3 = f3.midicps * LFNoise0.kr(SinOsc.kr(12).range(0.1, 1));
		f4 = f4.midicps * LFNoise0.kr(SinOsc.kr(12).range(0.1, 1));
		f5 = f5.midicps * LFNoise0.kr(SinOsc.kr(12).range(0.1, 1));

		sig = DynKlang.ar(`[[f1, f2, f2, f4, f5], [0.4, 0.4, 0.2, 0.5, 0.3], [phase, phase, phase, phase, phase]], 1, 0);
		amp = Dust.ar(1).exprange(0.5, 1.2);
		env = EnvGen.kr(Env.perc(0.01, 3, curve: -2), t_gate);
		sig = sig * amp;
		sig = sig * env;
		Out.ar(0, sig);

	}
).add;
)