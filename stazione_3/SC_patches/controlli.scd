x = Synth.new(\space);
y = Synth.new(\ele3);
j = Synth.new(\ele4);

// OSC messages *****************************************************************************************************************
(
t.free;
q.free;
p.free;
)

(
t = OSCFunc
(
{
	arg msg, time, addr, recvPort;
	//[msg, time, addr, recvPort].postln;
	x.set(\t_gate, msg[1]);
},
'/trigger0');
)
(
q = OSCFunc
(
{
	arg msg, time, addr, recvPort;
	//[msg, time, addr, recvPort].postln;
	if( msg[1]== 1, {z.start},{z.pause});
},
'/trigger1');
)
(
p = OSCFunc
(
{
	arg msg, time, addr, recvPort;
	//[msg, time, addr, recvPort].postln;
	if (msg[1]==1, {
		y.set(\t_gate, msg[1],  \duty, rrand(0.2, 0.8), \midi, ([0, 2, 4, 7, 9].choose)+([48, 60].choose));});

},
'/trigger2');
)
(
u = OSCFunc
(
{
	arg msg, time, addr, recvPort;
	if (msg[1]==1, {
		j.set(\t_gate, 1,
			\mod, 86,
			\freq, [0, 2, 4, 7, 9].choose );
	});
}, '\trigger3');
)

// Synth Algorythms ************************************************************************************************************

(

a = ["C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B"];
"event, midi, pitch, octave".postln;
z = Task({
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
z.pause;
)

// Synths Params + free *************************************************************************************************************
x.set(\maxdelTime, 1, \delTime, 0.8, \decTime, 3);
x.set(\noiseFreq, 4, \noiseMul, 36);
x.set(\sawfreqL, 4, \sawFreqR, 4.125, \sawMul, 1, \sawPhaseL, 0, \sawPhaseR, 0.5);
x.free;
y.free;
j.free;

s.quit;