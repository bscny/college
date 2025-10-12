using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    [SerializeField]
    private Transform Tank;
    [SerializeField]
    private Transform TankOrientation;
    [SerializeField]
    private Transform TankTower;
    [SerializeField]
    private Transform TankCannon;
    [SerializeField]
    private Transform TankShoulder;
    [SerializeField]
    private Rigidbody TankRB;

    [SerializeField]
    private float tankRotateSpeed;
    [SerializeField]
    private float slerpSpeed;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // tank
        Vector3 cam_tankDir = Tank.position - new Vector3(transform.position.x, Tank.position.y, transform.position.z);
        //Vector3 shoulder_camkDir = TankShoulder.position - new Vector3(transform.position.x, transform.position.y, transform.position.z);

        //TankOrientation.forward = cam_tankDir.normalized;
        TankOrientation.forward = Vector3.Slerp(TankOrientation.forward, cam_tankDir.normalized, Time.deltaTime * slerpSpeed);

        float horizontalInput;
        float verticalInput;

        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");
        Vector3 inputDir = TankOrientation.forward * verticalInput + TankOrientation.right * horizontalInput;

        if(inputDir != Vector3.zero)
        {
            Tank.forward = Vector3.Slerp(Tank.forward, inputDir, Time.deltaTime * tankRotateSpeed);

            //TankOrientation.forward = cam_tankDir.normalized;
            TankOrientation.forward = Vector3.Slerp(TankOrientation.forward, cam_tankDir.normalized, Time.deltaTime * slerpSpeed);
        }

        // cannon
        /*TankCannon.forward = shoulder_camkDir.normalized;
        Vector3 shoulder_camkDirWithoutY = new Vector3(shoulder_camkDir.x, 0, shoulder_camkDir.z);
        TankTower.forward = shoulder_camkDirWithoutY.normalized;*/
        TankTower.forward = cam_tankDir.normalized;
        //TankTower.forward = Vector3.Slerp(TankTower.forward, cam_tankDir.normalized, Time.deltaTime * slerpSpeed);
    }
}
