using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TankShoulderFollower : MonoBehaviour
{
    [SerializeField]
    private Transform Tank;
    [SerializeField]
    private Transform TankOrientation;
    [SerializeField]
    private float distance;
    [SerializeField]
    private float height;
    [SerializeField]
    private float scaleForward;
    [SerializeField]
    private float scaleRight;

    private Vector3 shoulder_tankDir;
    // Start is called before the first frame update
    void Start()
    {
        shoulder_tankDir = scaleRight * TankOrientation.right + scaleForward * TankOrientation.forward;
        transform.position = Tank.position + shoulder_tankDir.normalized * distance;
        transform.position += new Vector3(0, height, 0);
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        /*shoulder_tankDir = scaleRight * TankOrientation.right + scaleForward * TankOrientation.forward;
        transform.position = Tank.position + shoulder_tankDir.normalized * distance;
        transform.position += new Vector3(0, height, 0);*/

        Vector3 temp = Vector3.zero;
        shoulder_tankDir = scaleRight * TankOrientation.right + scaleForward * TankOrientation.forward;
        Vector3 final = Tank.position + shoulder_tankDir.normalized * distance + new Vector3(0, height, 0);
        transform.position = Vector3.SmoothDamp(transform.position, final, ref temp, 0.001f);
    }
}
