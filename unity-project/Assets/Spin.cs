using UnityEngine;
using System.Collections;

public class Spin : MonoBehaviour {
    // Use this for initialization
    void Start () {
    }

    // Update is called once per frame
    void Update () {
        // rotate at 90 degrees per second
        transform.Rotate(Vector3.up * Time.deltaTime*90);
    }
}