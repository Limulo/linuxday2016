
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

x = Synth.new(\space);

(
t = OSCFunc
(
{
	arg msg, time, addr, recvPort;
	//[msg, time, addr, recvPort].postln;
	x.set(\t_gate, msg[1]);
},
'/note0');
)
t.free;


x.set(\maxdelTime, 1, \delTime, 0.8, \decTime, 3);
x.set(\noiseFreq, 4, \noiseMul, 36);
x.set(\sawfreqL, 4, \sawFreqR, 4.125, \sawMul, 1, \sawPhaseL, 0, \sawPhaseR, 0.5);

x.set(\amp, 0.00);
x.free;
s.quit;