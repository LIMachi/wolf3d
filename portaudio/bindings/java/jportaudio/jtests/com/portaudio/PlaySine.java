
/** @file
 @ingroup bindings_java

 @brief Example that shows how to play sine waves using JPortAudio.
*/
package com.portaudio;

import com.portaudio.TestBasic.SineOscillator;

public class PlaySine
{
	/**
	 * Write a sine wave to the stream.
	 * @param stream
	 * @param framesPerBuffer
	 * @param numFrames
	 * @param sample_rate
	 */
	private void writeSineData( BlockingStream stream, int framesPerBuffer,
			int numFrames, int sample_rate )
	{
		float[] buffer = new float[framesPerBuffer * 2];
		SineOscillator osc1 = new SineOscillator( 200.0, sample_rate );
		SineOscillator osc2 = new SineOscillator( 300.0, sample_rate );
		int framesLeft = numFrames;
		while( framesLeft > 0 )
		{
			int index = 0;
			int framesToWrite = (framesLeft > framesPerBuffer) ? framesPerBuffer
					: framesLeft;
			for( int j = 0; j < framesToWrite; j++ )
			{
				buffer[index++] = (float) osc1.next();
				buffer[index++] = (float) osc2.next();
			}
			stream.write( buffer, framesToWrite );
			framesLeft -= framesToWrite;
		}
	}

	/**
	 * Create a stream on the default device then play sine waves.
	 */
	public void play()
	{
		PortAudio.initialize();

		// Get the default device and setup the stream parameters.
		int deviceId = PortAudio.getDefaultOutputDevice();
		DeviceInfo deviceInfo = PortAudio.getDeviceInfo( deviceId );
		double sample_rate = deviceInfo.defaultSampleRate;
		System.out.println( "  deviceId    = " + deviceId );
		System.out.println( "  sample_rate  = " + sample_rate );
		System.out.println( "  device name = " + deviceInfo.name );

		StreamParameters streamParameters = new StreamParameters();
		streamParameters.channelCount = 2;
		streamParameters.device = deviceId;
		streamParameters.suggestedLatency = deviceInfo.defaultLowOutputLatency;
		System.out.println( "  suggestedLatency = "
				+ streamParameters.suggestedLatency );

		int framesPerBuffer = 256;
		int flags = 0;
		
		// Open a stream for output.
		BlockingStream stream = PortAudio.openStream( null, streamParameters,
				(int) sample_rate, framesPerBuffer, flags );

		int numFrames = (int) (sample_rate * 4); // enough for 4 seconds

		stream.start();

		writeSineData( stream, framesPerBuffer, numFrames, (int) sample_rate );

		stream.stop();
		stream.close();

		PortAudio.terminate();
		System.out.println( "JPortAudio test complete." );
	}

	public static void main( String[] args )
	{
		PlaySine player = new PlaySine();
		player.play();
	}
}
