using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class TrackingDisplay : MonoBehaviour {

	public string textPrefix = "";
	public int decimalPlaces = 3;

	void Update() {
		Vector3 pos = new Vector3(
			MainActivity.activityObj.Call<float>("getTranslationX"),
			-MainActivity.activityObj.Call<float>("getTranslationY"),
			MainActivity.activityObj.Call<float>("getTranslationZ")
			);

		GetComponent<Text>().text = textPrefix + pos.ToString("F" + decimalPlaces.ToString());
	}
}
