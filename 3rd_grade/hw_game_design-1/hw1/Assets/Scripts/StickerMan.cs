using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StickerMan : MonoBehaviour
{
    public float walk_speed = 10f;
    public float jump_force = 500f;

    public float walk_speed_up = 2f;
    public float jump_force_up = 100f;

    bool isOnGround;
    Animator animator;
    Rigidbody2D rbody2D;
    float dirx;

    bool freeze;

    // Start is called before the first frame update
    void Start()
    {
        rbody2D = gameObject.GetComponent<Rigidbody2D>();
        animator = gameObject.GetComponent<Animator>();
        isOnGround = false;
        freeze = false;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (freeze == true) 
        {
            return;
        }

        dirx = Input.GetAxisRaw("Horizontal");
        rbody2D.velocity = new Vector2(dirx * walk_speed, rbody2D.velocity.y);  // horizontal movement

        if (Input.GetKey(KeyCode.Space) && isOnGround)   // make it jump
        {
            Vector2 force2D = new Vector2(0f, jump_force);
            isOnGround = false;
            rbody2D.AddForce(force2D);
        }

        if (!isOnGround)   // switch anime to jump
        {
            animator.SetInteger("state", 2);
        }
        else if (dirx != 0)   // switch anime to move
        {
            animator.SetInteger("state", 1);
        }
        else    // switch anime to stand
        {    
            animator.SetInteger("state", 0);
        }

        if (dirx * this.transform.localScale.x < 0)   //  switch side
        {
            this.transform.localScale = new Vector3(-1 * this.transform.localScale.x, this.transform.localScale.y, this.transform.localScale.z);
        }


        this.transform.rotation = Quaternion.Euler(0, 0, 0);
    }

    void OnCollisionEnter2D(Collision2D collision)  // touch the ground
    {
        isOnGround = true;
    }
    public bool Get_isOnGround()
    { 
        return isOnGround;
    }

    public float Get_Velocity()
    {
        return rbody2D.velocity.y;
    }

    public float Get_dir_X()
    {
        return this.transform.localScale.x;
    }

    public Vector3 Get_Pos()
    {
        return this.transform.position;
    }

    public void DisActivated() 
    {
        freeze = true;
        animator.SetInteger("state", 0);
    }
    public void OnTriggerStay2D(Collider2D other)
    {
        if (other.name == "Sword")
        {
            //print("check");
        }
        else
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Player_got_hurt();
        }
    }

    public void OnTriggerEnter2D(Collider2D other) 
    {
        if (other.name == "health potion")
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Player_health_potion();
        }
        else if (other.name == "mana potion")
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Player_mana_potion();
        }
        else if (other.name == "strength potion") 
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Player_strength_potion();
        }
    }

    public void SpeedUp() 
    {
        walk_speed *= walk_speed_up;
        jump_force += jump_force_up;
    }

    public void SpeedDown() 
    {
        walk_speed /= walk_speed_up;
        jump_force -= jump_force_up;
    }
}
