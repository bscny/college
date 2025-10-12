using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TankController : MonoBehaviour
{
    [SerializeField]
    private float moveSpeed;
    [SerializeField] 
    private float wheelRotateSpeed;
    [SerializeField] 
    private float drag;
    [SerializeField]
    private float cannonRotateSpeed;
    [SerializeField]
    private Transform orientation;
    [SerializeField]
    private Transform cannon;
    [SerializeField]
    private GameObject[] Wheels = new GameObject[4];

    private float horizontalInput;
    private float verticalInput;

    private float cannonUp;
    private float cannonDown;

    private Vector3 inputDir;

    private Rigidbody rb;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        rb.freezeRotation = true;
        rb.drag = drag;

        //moveSpeed = moveSpeed / Time.deltaTime;
    }

    // Update is called once per frame
    void Update()
    {
        ControllInput();
    }

    private void FixedUpdate()
    {
        Driving();
        AdjustCannonAngle();
    }

    private void ControllInput()
    {
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");

        if (Input.GetKey(KeyCode.E))
        {
            cannonUp = 1;
        }
        else
        {
            cannonUp= 0;
        }

        if (Input.GetKey(KeyCode.Q))
        {
            cannonDown = 1;
        }
        else
        {
            cannonDown= 0;
        }
    }

    private void Driving()
    {
        inputDir = orientation.forward * verticalInput + orientation.right * horizontalInput;

        rb.AddForce(inputDir.normalized * moveSpeed * 10, ForceMode.Force);

        Vector3 currentSpeed = new Vector3(rb.velocity.x, 0, rb.velocity.z);

        if(currentSpeed != Vector3.zero)
        {
            foreach(GameObject wheel in Wheels)
            {
                if(wheel != null)
                {
                    wheel.transform.Rotate(wheelRotateSpeed * 10, 0, 0, Space.Self);
                }
            }
        }

        if(currentSpeed.magnitude > moveSpeed)
        {
            Vector3 correctSpeed = currentSpeed.normalized * moveSpeed;
            rb.velocity = new Vector3(correctSpeed.x, rb.velocity.y, correctSpeed.z);
        }
    }

    private void AdjustCannonAngle()
    {
        if(cannonUp == 1 && cannon.rotation.x > -0.45)
        {
            cannon.Rotate(-cannonRotateSpeed, 0, 0);
        }

        if(cannonDown == 1 && cannon.rotation.x < 0.45)
        {
            cannon.Rotate(cannonRotateSpeed, 0, 0);
        }
    }
}
