using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class GameManager : MonoBehaviour
{
    [SerializeField]
    private int WinConditionTime = 180;
    [SerializeField]
    private float MAX_INV_TIME;
    [SerializeField] 
    private float MAX_FR_TIME;
    [SerializeField]
    private float DMG_PER_HIT;
    [SerializeField]
    private float HEAL_PER_BOX;
    [SerializeField]
    private float REDUCE_PER_BOX;

    [SerializeField]
    private TextMeshProUGUI _TimeLeft;
    [SerializeField]
    private BarController HpBar;
    [SerializeField]
    private BarController InvBar;
    [SerializeField]
    private BarController FRBar;
    [SerializeField]
    private GameObject TankBulletSpawner;
    [SerializeField]
    private GameObject GameOverUI;
    [SerializeField]
    private TextMeshProUGUI _Message;


    private float playerHp;
    private float inVincibleTime;
    private bool isInvincible;
    private float freeReloadTime;
    private bool isFreeReload;

    private float timeLeft;

    private int killEnemyNum;
    // Start is called before the first frame update
    void Start()
    {
        GameOverUI.SetActive(false);
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
        _TimeLeft.text = "You Still Need To Survive For " + WinConditionTime + " second";

        HpBar.Init(100, 100);
        InvBar.Init(MAX_INV_TIME, 0);
        FRBar.Init(MAX_FR_TIME, 0);

        playerHp = 100;
        inVincibleTime = 0;
        freeReloadTime = 0;

        isFreeReload = false;
        isInvincible = false;

        timeLeft = WinConditionTime;

        killEnemyNum = 0;
    }

    // Update is called once per frame
    void Update()
    {
        SurviveCheck();
        InvCheck();
        FreeReloadCheck();

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if(Cursor.lockState == CursorLockMode.Locked)
            {
                Cursor.lockState = CursorLockMode.None;
                Cursor.visible = true;
            }
            else
            {
                Cursor.lockState = CursorLockMode.Locked;
                Cursor.visible = false;
            }
        }
    }

    private void SurviveCheck()
    {
        timeLeft -= Time.deltaTime;

        _TimeLeft.text = "You Still Need To Survive For " + (int)timeLeft + " second";

        if(timeLeft <= 0)
        {
            // win
            GameOverUI.SetActive(true);
            _Message.text = "You Win\r\nTotal kill: " + killEnemyNum;
            Cursor.lockState = CursorLockMode.None;
            Cursor.visible = true;
        }
    }

    private void InvCheck()
    {
        if (isInvincible) 
        {
            inVincibleTime -= Time.deltaTime;
        }
        else
        {
            return;
        }

        if(inVincibleTime <= 0)
        {
            inVincibleTime = 0;
            isInvincible = false;
        }

        InvBar.SetVal(inVincibleTime);
    }

    private void FreeReloadCheck()
    {
        if (isFreeReload)
        {
            freeReloadTime -= Time.deltaTime;
        }
        else
        {
            return;
        }

        if(freeReloadTime <= 0)
        {
            freeReloadTime = 0;
            isFreeReload = false;
            TankBulletSpawner.GetComponent<BulletSpawner>().SwitchFireRate();
        }

        FRBar.SetVal(freeReloadTime);
    }


    // publics'

    public void SetInvincible()
    {
        isInvincible = true;

        inVincibleTime = MAX_INV_TIME;
        InvBar.SetVal(MAX_INV_TIME);
    }

    public void SetFreeReload()
    {
        isFreeReload = true;
        TankBulletSpawner.GetComponent<BulletSpawner>().SwitchFireRate();

        freeReloadTime = MAX_FR_TIME;
        FRBar.SetVal(MAX_FR_TIME);
    }
    public void Heal()
    {
        playerHp += HEAL_PER_BOX;

        if(playerHp > 100)
        {
            playerHp = 100;
        }

        HpBar.SetVal(playerHp);
    }
    public void ReduceTime()
    {
        timeLeft -= REDUCE_PER_BOX;

        if(timeLeft <= 0)
        {
            _TimeLeft.text = "You Still Need To Survive For 0 second";

            // win
            GameOverUI.SetActive(true);
            _Message.text = "You Win\r\nTotal kill: " + killEnemyNum;
            Cursor.lockState = CursorLockMode.None;
            Cursor.visible = true;
        }
    }
    public void Damage()
    {
        if (isInvincible)
        {
            return;
        }

        playerHp -= DMG_PER_HIT;

        if(playerHp <= 0)
        {
            HpBar.SetVal(0);
            // lose
            GameOverUI.SetActive(true);
            _Message.text = "You Lose\r\n" + (int)timeLeft + " seconds left to hold";
            Cursor.lockState = CursorLockMode.None;
            Cursor.visible = true;
        }
        else
        {
            HpBar.SetVal(playerHp);
        }
    }

    public void KillEnemy()
    {
        killEnemyNum++;
    }
}
