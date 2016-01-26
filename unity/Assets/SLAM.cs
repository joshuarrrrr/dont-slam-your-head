using UnityEngine;
using System.Collections;

public class SLAM : MonoBehaviour {

	private Vector3 startPosition;
	private Quaternion startRotation;

	private bool useTrackingPosition = false;
	private bool useTrackingRotation = false;

	private float lastResetTime = 0.0F;
	private float resetTimeout = 1.0F;

	// Use this for initialization
	void Start () {
		Transform transform = GetComponent<Transform>();
		startPosition = transform.position;
		startRotation = transform.rotation;
	}

	// Update is called once per frame
	void Update () {
		if (useTrackingPosition) {
			Vector3 trackingPosition = new Vector3(
				MainActivity.activityObj.Call<float>("getTranslationX"),
				MainActivity.activityObj.Call<float>("getTranslationY"),
				MainActivity.activityObj.Call<float>("getTranslationZ")
				);
			transform.position = startPosition + trackingPosition;
		}
		if (useTrackingRotation) {
			Quaternion quat = new Quaternion(
				MainActivity.activityObj.Call<float>("getRotationX"),
				MainActivity.activityObj.Call<float>("getRotationY"),
				MainActivity.activityObj.Call<float>("getRotationZ"),
				MainActivity.activityObj.Call<float>("getRotationW")
				);
			transform.rotation = quat;
		}

		if ((getTouchCount() >= 3) && (Time.time >= lastResetTime + resetTimeout)) {
			this.Reset();
		}
	}

	int getTouchCount() {
		int count = 0;
        foreach (Touch touch in Input.touches) {
            if (touch.phase != TouchPhase.Ended && touch.phase != TouchPhase.Canceled)
                count++;
        }
        return count;
	}

	public void Reset() {
		MainActivity.activityObj.Call("resetSLAM");
		lastResetTime = Time.time;
		transform.position = startPosition;
		transform.rotation = startRotation;
		Debug.Log("RESET");
	}
}
