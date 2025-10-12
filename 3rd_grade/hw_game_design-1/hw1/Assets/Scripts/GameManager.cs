using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;
using UnityEngine.SocialPlatforms.Impl;
using UnityEditor;

public class GameManager : MonoBehaviour
{
    public TextMeshProUGUI p_hp;
    public TextMeshProUGUI p_np;
    public TextMeshProUGUI p_xp;
    public TextMeshProUGUI e_hp;
    public TextMeshProUGUI e_np;
    public TextMeshProUGUI e_xp;

    public TextMeshProUGUI winner;
    public GameObject GameOverUI;
    public GameObject[] potion_arr = new GameObject[3];

    public int INTERVAL = 400;
    public float damage_per_update = 0.5f;
    float ratio_damage_per_update_enemy;
    public float recovery_per_potion = 30f;
    public float NP_per_potion = 100;
    public float NP_reduce_per_update = 0.2f;
    public float XP_per_potion = 100;
    public float XP_reduce_per_update = 0.1f;

    float player_hp;
    float enemy_hp;
    bool potionExist;
    int interval_potion;
    float player_np;
    bool player_isEnhanced;
    float enemy_np;
    bool enemy_isEnhanced;
    float player_xp;
    bool player_isSpeedUp;
    float enemy_xp;
    bool enemy_isSpeedUp;

    bool IsOver;

    // Start is called before the first frame update
    void Start()
    {
        player_hp = 100;
        enemy_hp = 100;
        player_np = 0;
        enemy_np = 0;
        player_xp = 0;
        enemy_xp = 0;
        IsOver = false;
        potionExist = false;
        interval_potion = 0;
        player_isEnhanced = false;
        enemy_isEnhanced = false;
        player_isSpeedUp = false;
        enemy_isSpeedUp = false;

        ratio_damage_per_update_enemy = 1;

        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;  
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // player enemy helth controll (end game condition)
        if (player_hp <= 0 && IsOver == false)  // player loses...
        {
            GameOverUI.SetActive(true);
            GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().DisActivated();
            GameObject.Find("StickerMan").GetComponent<StickerMan>().DisActivated();
            winner.text = "GG YOU LOSE...";

            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;

            IsOver = true;
        }
        else if (enemy_hp <= 0 && IsOver == false)  // enemy loses ^^
        {
            GameOverUI.SetActive(true);
            GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().DisActivated();
            GameObject.Find("StickerMan").GetComponent<StickerMan>().DisActivated();
            winner.text = "GG YOU WIN ^^";

            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;

            IsOver = true;
        }

        // potion functions
        if (potionExist == false && interval_potion == 0)  // generate potion
        {
            int rand = Random.Range(0, 3);

            potion_arr[rand].SetActive(true);

            potionExist = true;
            interval_potion = INTERVAL;
        }
        else if(potionExist == false && interval_potion > 0)
        {
            interval_potion--;
        }

        if (player_isEnhanced == false && player_np > 0)  // lengthing the sword for player
        {
            GameObject.Find("Sword").GetComponent<Sword>().lengthing();

            player_np -= NP_reduce_per_update;
            GameObject.Find("Player_NPBar").GetComponent<Player_NPBar>().Set_NP(player_np);
            p_np.text = "NP: " + (int)player_np;
            player_isEnhanced = true;
        }
        else if (player_isEnhanced == true && player_np > 0)
        {
            player_np -= NP_reduce_per_update;
            GameObject.Find("Player_NPBar").GetComponent<Player_NPBar>().Set_NP(player_np);
            p_np.text = "NP: " + (int)player_np;
        }
        else if (player_isEnhanced == true && player_np <= 0) 
        {
            GameObject.Find("Sword").GetComponent<Sword>().dislengthing();

            player_np = 0;
            GameObject.Find("Player_NPBar").GetComponent<Player_NPBar>().Set_NP(player_np);
            p_np.text = "NP: " + (int)player_np;
            player_isEnhanced = false;
        }

        if (enemy_isEnhanced == false && enemy_np > 0)  // lengthing the sword for enemy
        {
            GameObject.Find("Sword (enemy)").GetComponent<Enemy_sword>().lengthing();

            enemy_np -= NP_reduce_per_update;
            GameObject.Find("Enemy_NPBar").GetComponent<Enemy_NPBar>().Set_NP(enemy_np);
            e_np.text = "NP: " + (int)enemy_np;
            enemy_isEnhanced = true;
        }
        else if (enemy_isEnhanced == true && enemy_np > 0)
        {
            enemy_np -= NP_reduce_per_update;
            GameObject.Find("Enemy_NPBar").GetComponent<Enemy_NPBar>().Set_NP(enemy_np);
            e_np.text = "NP: " + (int)enemy_np;
        }
        else if (enemy_isEnhanced == true && enemy_np <= 0)
        {
            GameObject.Find("Sword (enemy)").GetComponent<Enemy_sword>().dislengthing();

            enemy_np = 0;
            GameObject.Find("Enemy_NPBar").GetComponent<Enemy_NPBar>().Set_NP(enemy_np);
            e_np.text = "NP: " + (int)enemy_np;
            enemy_isEnhanced = false;
        }

        if(player_isSpeedUp == false && player_xp > 0)  // speed up for player
        {
            GameObject.Find("StickerMan").GetComponent<StickerMan>().SpeedUp();

            player_xp -= XP_reduce_per_update;
            GameObject.Find("Player_XPBar").GetComponent<Player_XPBar>().Set_XP(player_xp);
            p_xp.text = "XP: " + (int)player_xp;
            player_isSpeedUp = true;
        }
        else if (player_isSpeedUp == true && player_xp > 0)
        {
            player_xp -= XP_reduce_per_update;
            GameObject.Find("Player_XPBar").GetComponent<Player_XPBar>().Set_XP(player_xp);
            p_xp.text = "XP: " + (int)player_xp;
        }
        else if (player_isSpeedUp == true && player_xp <= 0)
        {
            GameObject.Find("StickerMan").GetComponent<StickerMan>().SpeedDown();

            player_xp = 0;
            GameObject.Find("Player_XPBar").GetComponent<Player_XPBar>().Set_XP(player_xp);
            p_xp.text = "XP: " + (int)player_xp;
            player_isSpeedUp = false;
        }

        if (enemy_isSpeedUp == false && enemy_xp > 0)  // speed up for enemy
        {
            GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().SpeedUp();

            enemy_xp -= XP_reduce_per_update;
            GameObject.Find("Enemy_XPBar").GetComponent<Enemy_XPBar>().Set_XP(enemy_xp);
            e_xp.text = "XP: " + (int)enemy_xp;
            enemy_isSpeedUp = true;
        }
        else if (enemy_isSpeedUp == true && enemy_xp > 0)
        {
            enemy_xp -= XP_reduce_per_update;
            GameObject.Find("Enemy_XPBar").GetComponent<Enemy_XPBar>().Set_XP(enemy_xp);
            e_xp.text = "XP: " + (int)enemy_xp;
        }
        else if (enemy_isSpeedUp == true && enemy_xp <= 0)
        {
            GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().SpeedDown();

            enemy_xp = 0;
            GameObject.Find("Enemy_XPBar").GetComponent<Enemy_XPBar>().Set_XP(enemy_xp);
            e_xp.text = "XP: " + (int)enemy_xp;
            enemy_isSpeedUp = false;
        }
    }

    //  DAMAGING---------------------------------------------
    public void Player_got_hurt() 
    {
        if (player_hp > 0 && IsOver == false)
        {
            player_hp -= (damage_per_update * ratio_damage_per_update_enemy);
            GameObject.Find("Player_HPBar").GetComponent<Player_HPBar>().Set_health(player_hp);
            p_hp.text = "HP: " + (int)player_hp;
        }
    }

    public void Enemy_got_hurt()
    {
        if (enemy_hp > 0 && IsOver == false)
        {
            enemy_hp -= damage_per_update;
            GameObject.Find("Enemy_HPBar").GetComponent<Enemy_HPBar>().Set_HP(enemy_hp);
            e_hp.text = "HP: " + (int)enemy_hp;
        }
    }

    // HEALING----------------------------------------------------
    public void Player_health_potion() 
    {
        if (player_hp + recovery_per_potion > 100)
        {
            player_hp = 100;
        }
        else 
        { 
            player_hp += recovery_per_potion;
        }

        GameObject.Find("Player_HPBar").GetComponent<Player_HPBar>().Set_health(player_hp);
        p_hp.text = "HP: " + (int)player_hp;
        potion_arr[0].SetActive(false);
        potionExist = false;
    }

    public void Enemy_health_potion()
    {
        if (enemy_hp + recovery_per_potion > 100)
        {
            enemy_hp = 100;
        }
        else
        {
            enemy_hp += recovery_per_potion;
        }

        GameObject.Find("Enemy_HPBar").GetComponent<Enemy_HPBar>().Set_HP(enemy_hp);
        e_hp.text = "HP: " + (int)enemy_hp;
        potion_arr[0].SetActive(false);
        potionExist = false;
    }

    // SWORD LENGTHING-----------------------------------------
    public void Player_mana_potion() 
    {
        if (player_np + NP_per_potion > 100)
        {
            player_np = 100;
        }
        else
        {
            player_np += NP_per_potion;
        }
        GameObject.Find("Player_NPBar").GetComponent<Player_NPBar>().Set_NP(player_np);
        p_np.text = "NP: " + (int)player_np;

        potion_arr[1].SetActive(false);
        potionExist = false;
    }
    public void Enemy_mana_potion()
    {
        if (enemy_np + NP_per_potion > 100)
        {
            enemy_np = 100;
        }
        else
        {
            enemy_np += NP_per_potion;
        }
        GameObject.Find("Enemy_NPBar").GetComponent<Enemy_NPBar>().Set_NP(enemy_np);
        e_np.text = "NP: " + (int)enemy_np;

        potion_arr[1].SetActive(false);
        potionExist = false;
    }

    // SPEEDING up-------------------------------------------
    public void Player_strength_potion() 
    {
        if (player_xp + XP_per_potion > 100)
        {
            player_xp = 100;
        }
        else
        {
            player_xp += XP_per_potion;
        }
        GameObject.Find("Player_XPBar").GetComponent<Player_XPBar>().Set_XP(player_xp);
        p_xp.text = "XP: " + (int)player_xp;

        potion_arr[2].SetActive(false);
        potionExist = false;
    }

    public void Enemy_strength_potion()
    {
        if (enemy_xp + XP_per_potion > 100)
        {
            enemy_xp = 100;
        }
        else
        {
            enemy_xp += XP_per_potion;
        }
        GameObject.Find("Enemy_XPBar").GetComponent<Enemy_XPBar>().Set_XP(enemy_xp);
        e_xp.text = "XP: " + (int)enemy_xp;

        potion_arr[2].SetActive(false);
        potionExist = false;
    }

    // end game control pannel
    public void Restart() 
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }

    public void Quit()
    {
        Application.Quit();
    }

    // for different LV of enemy
    public float Get_enemyHP() 
    {
        return enemy_hp;
    }

    public void Double_enemy_strike_power() 
    {
        ratio_damage_per_update_enemy = 2;
    }
}
