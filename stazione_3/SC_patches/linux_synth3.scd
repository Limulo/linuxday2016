
(
SynthDef.new(\space, {
	arg amp = 0.8, maxDelTime = 1, delTime= 0.3, decTime = 2, noiseFreq=3, noiseMul=24, sawFreqL=5, sawFreqR= 5.123, sawMul=3, sawAdd=80, sawPhaseL=0, sawPhaseR=0.125;
	var freq, sig;
	freq = midicps(
		LFNoise1.ar(
			freq: noiseFreq,
			mul: noiseMul,
			add: LFSaw.ar(
				freq: [sawFreqL, sawFreqR],
				iphase: [sawPhaseL, sawPhaseR],
				mul: sawMul,
				add: sawAdd)));
	sig = SinOsc.ar(freq, 0, 0.4);
	sig = CombN.ar(sig, 1, 0.3, 2);
	Out.ar(0, sig*amp);
}).add;
)

x = Synth.new(\space);
x.set(\maxdelTime, 1, \delTime, 0.8, \decTime, 3);
x.set(\noiseFreq, 4, \noiseMul, 36);
x.set(\sawfreqL, 4, \sawFreqR, 4.125, \sawMul, 1, \sawPhaseL, 0, \sawPhaseR, 0.5);

x.set(\amp, 0.00);
x.free;