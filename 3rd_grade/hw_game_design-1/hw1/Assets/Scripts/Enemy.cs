using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    public TextMeshProUGUI boss_mode;

    public float walk_speed = 2.5f;
    public float jump_force = 250f;

    public float walk_speed_up = 2f;
    public float jump_force_up = 100f;

    public float rank_up_walk = 2.5f;
    public float rank_up_jump = 250f;

    bool isOnGround;
    float dirx;
    Animator animator;
    Rigidbody2D rbody2D;
    float player_x;
    float player_y;

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
        player_x = GameObject.Find("StickerMan").GetComponent<StickerMan>().Get_Pos().x;

        // horizontal movement
        if (this.transform.position.x < player_x)
        {
            rbody2D.velocity = new Vector2(walk_speed, rbody2D.velocity.y);

            dirx = 1f;
        }
        else if (this.transform.position.x > player_x)
        {
            rbody2D.velocity = new Vector2(-walk_speed, rbody2D.velocity.y);

            dirx = -1f;
        }
        else {
            rbody2D.velocity = new Vector2(0, rbody2D.velocity.y);

            dirx = 0;
        }

        player_y = GameObject.Find("StickerMan").GetComponent<StickerMan>().Get_Pos().y;

        // vertical movement
        if (player_y - 1 > this.transform.position.y && isOnGround)   // make it jump
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

        // for different LV of enemy
        float hp = GameObject.Find("GameManager").GetComponent<GameManager>().Get_enemyHP();

        if (hp > 75)  // init mode
        {
            boss_mode.text = "First Mode";
        }
        else if (hp > 50)  // 2nd mode
        {
            walk_speed = rank_up_walk * 2;
            jump_force = rank_up_jump * 2;

            boss_mode.text = "Second Mode";
        }
        else if (hp > 25) // 3rd mode
        {
            walk_speed = rank_up_walk * 3;
            jump_force = rank_up_jump * 3;

            boss_mode.text = "Third Mode";
        }
        else 
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Double_enemy_strike_power();

            boss_mode.text = "Final Mode";
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
        if (other.name == "Sword (enemy)")
        {
            //print("check");
        }
        else
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Enemy_got_hurt();
        }
    }
    public void OnTriggerEnter2D(Collider2D other)
    {
        if (other.name == "health potion")
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Enemy_health_potion();
        }
        else if (other.name == "mana potion")
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Enemy_mana_potion();
        }
        else if (other.name == "strength potion")
        {
            GameObject.Find("GameManager").GetComponent<GameManager>().Enemy_strength_potion();
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
