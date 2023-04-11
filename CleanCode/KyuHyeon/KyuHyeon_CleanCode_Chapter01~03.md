# CleanCode 01 ~ 03

## 1장 깨끗한 코드

1장은 이 책의 의미에 대한 고찰로 시작된다.

독자가 이 책을 읽는 이유는 좋은 코드를 작성하기 위함일 것이다.

그렇다면 좋은 코드란 무엇일까?

저자는 이 의문에 대해 여러 전문가들의 의견을 소개한다.

조금씩 차이는 있지만 대부분의 전문가들은 좋은 코드는 읽기 쉬운 코드라고 말한다.

조금 더 설명하자면, 그 분야의 경력이 긴 전문가 뿐만 아니라 누가 읽어도 읽기 쉽고 이해하기 쉬운 코드라고 생각한다.

그렇다면 반대로 나쁜 코드란 읽기 어렵고 이해하기 어려운 코드라고 정의할 수 있을 것이다.

어떤 코드든 처음부터 나쁜 코드는 없을 것이다.

그러나 시간이 지나면서 코드는 점점 나쁜 코드로 변해간다.

이유는 여러가지가 있겠지만, 결국 원인은 코드를 작성하는 사람이 좋은 코드를 작성하는 것을 포기했기 때문이다.

시간이 없어서, 다른 더 중요한 일이 있어서, 나쁜 코드인걸 알지만 어쩔 수 없다는 말과 "나중에"라며 미루었기 때문일 것이다.

결국 나쁜 코드를 작성하게 되는 모든 상황에 대한 한마디의 정리가 가능했다.

> "나중은 결코 오지 않는다." - 르블랑의 법칙

이러한 말은 이제 막 회사에 취업한 주니어 프로그래머인 나에게 크게 와닿는 말이었다.

당장 주어진 일을 하기 바쁘고 정해진 시간 내에 결과물을 내야 하는 회사에서는 "나중에"라는 핑계를 대며 나쁜 코드를 작성하곤 했다.

하지만 이제는 나중이 오지 않는다는 말을 떠올리며 시간을 들여서라도 좋은 코드를 작성하는 것이 가장 빠른 길이라는 것을 의식하게 되었다.

## 2장 의미 있는 이름

이름에는 힘이 있다.

인간의 기억력에는 한계가 있는 법이고 프로그래머가 신경써야 할 점은 너무나도 많다.

그런 의미에서 이름은 프로그래머에게 있어서 일종의 외부 기억장치로서의 역할을 가지고 있다고 생각한다.

프로그래밍을 처음 배우는 사람에게 변수를 상자에 비유하여 표현하곤 한다.

매우 작은 프로그램이라면 단순히 상자에 a, b 등의 이름을 지어도 크게 문제될 것은 없을 것이다.

그러나 프로그램이 커지고 복잡해지면 변수의 이름은 더욱 중요해진다.

수백, 수천 개의 상자들을 전부 기억할 수 있는 사람은 없을 것이다.

최소한, 나는 그럴 수 없다.

프로그래밍에는 주석이라는 개념과 시스템이 있지만, 사실 좋은 코드일수록 주석의 필요성은 낮아지고 오히려 주석이 없을수록 보기 편해진다.

좋은 이름을 가진 변수와 메서드명은 좋은 코드를 작성하기 위한 첫걸음이라고 생각한다.

## 3장 함수

함수는 코드를 작성하는 가장 기본적인 단위이다.

이 장에서 저자는 좋은 코드를 작성하기 위한 함수 작성법에 대해 설명한다.

저자의 논지는 함수는 최소한의 단위로 작성하며 함수는 한 가지 일만 해야 한다는 것이다.

또한 실제로 작성되는 함수의 코드들도 작으면 작을 수록 좋다는 것이다.

함수가 작을수록 함수의 이름만 보고도 함수가 어떤 일을 하는지 알 수 있고, 함수의 코드를 읽는 시간도 줄어들기 때문일 것이다.

실제로 프로그래머는 코드를 작성하는 시간보다 코드를 읽는 시간이 압도적으로 길다. 

특히 현업에서는 프로젝트 초창기가 아니라면 많은 사람들이 이미 수많은 코드를 작성한 상태이다.

이런 상황에서 간단한 버그를 해결하는 일이라도 수많은 코드를 읽어야만 그 문제를 해결할 수 있다.

내가 참여하고 있는 프로젝트에서도 다양한 크기의 함수들이 존재한다.

저자의 주장이 어떠한 상황에도 옳다는 것은 아니지만 작은 함수를 통해 읽기 좋게 쓰여진 코드는 읽고 이해하는 시간이 짧아지는 것을 경험 했다.

이런 작은 메서드 들을 잘 활용한다면 코드를 작성하는 프로그래머 뿐만 아니라 그 코드를 보게될 다른 사람들에게도 도움이 된다는 점을 알게 되었다.

## 활용

아래 코드는 실제 내가 참여중인 프로젝트에서 작성되어 있던 코드이다.

간단하게 코드에 대해 설명하자면 랭킹 리스트 슬롯을 관리하는 코드이며 유니티의 UI 요소를 관리하는 이 프로젝트 내에서는 작은 클래스이다.

내가 해야할 일감은 랭킹의 score를 소숫점 둘째 자리에서 버림 처리를 하고 scoreText를 소숫점 한자리까지 표시하는 간단한 일감이었다.

작업 내용 자체는 간단했지만 클린코드를 읽으며 느낀점과 배운점을 활용하여 이 코드를 리팩토링 해보았다.

```C#
public class RankingUserListSlot : UIElement
{
    [SerializeField] private MemberSlot m_memberSlot;

    [SerializeField] private TextMeshProUGUI m_score;
    [SerializeField] private Image m_rankImage;
    [SerializeField] private TextMeshProUGUI m_rankText;

    [SerializeField] private GameObject m_myRank;

    private RankingInfoDesc m_rankingInfoDesc = new RankingInfoDesc();

    public void SetRanking(RankingTypeEnum rankingType, PKS_RANKING_INFO pks)
    {
        int rank = pks.rank;
        if (rank <= 3)
        {
            m_rankImage.enabled = true;
            m_rankImage.sprite = UIUtil.GetIcon("Common00", $"Rank{rank}nd");

            m_rankText.text = "";
        }
        else
        {
            m_rankImage.enabled = false;
            m_rankText.text = rank.ToString();
        }

        m_score.text = GetScoreByRankingType(rankingType, pks.currentValue);

        // desc
        m_rankingInfoDesc.Init(pks.desc);
        m_memberSlot.SetMember(pks.aid, pks.accountName, m_rankingInfoDesc.TitleName, m_rankingInfoDesc.GuildName, false,
            m_rankingInfoDesc.Level, m_rankingInfoDesc.ProfileSkinID, null, m_rankingInfoDesc.GenderType);
        var jobData = JobAMData.FromTable(m_rankingInfoDesc.JobID);
        m_memberSlot.SetHeadImage(jobData);

        //m_memberSlotButton.onClick.RemoveAllListeners();
        //m_memberSlotButton.onClick.AddListener(() =>
        //{
        //    var profileUI = UIManager.GetUIElement<ProfileUI>();

        //    if (ClientData.GetAccountData().AccountInst.m_guid == pks.aid)
        //        profileUI.ShowMyInfo();
        //    else
        //        profileUI.Show(pks.aid);
        //});

        bool myRank = pks.aid == ClientData.GetAccountGUID();
        m_myRank.SetActive(myRank);
    }

    private string GetScoreByRankingType(RankingTypeEnum rankingType, int score)
    {
        string scoreText = score.ToString();

        switch (rankingType)
        {
            case RankingTypeEnum.Level:
                {
                    int level = 0;
                    long maxExp = 0;
                    var expTable = Manager.GetEXPTable(Strings.Character);
                    EXPCalculate.GetEXP(expTable, score, 1, out level, out maxExp);

                    double percent = score / maxExp;
                    scoreText = $"Lv.{level} ({string.Format("{0:0.00}", percent)}%)";
                }
                break;

            case RankingTypeEnum.Combat:
                scoreText = UIUtil.GetCommaedText(score);               
                break;

            case RankingTypeEnum.RecordItem:
                {
                    int maxCount = Manager.GetItemMasterTable().ConditionMaxCount;
                    scoreText = $"{score}/{maxCount} ({((float)score / maxCount) * 100:0}%)";
                }
                break;

            case RankingTypeEnum.RecordRelationship:
                {
                    int maxCount = Manager.GetRecordRelationshipTable().ConditionMaxCount;
                    scoreText = $"{score}/{maxCount} ({((float)score / maxCount) * 100:0}%)";
                }
                break;

            case RankingTypeEnum.Adventure:
                {
                    int maxCount = Manager.GetQuestTable().AdventureMaxCount;
                    scoreText = $"{score}/{maxCount} ({((float)score / maxCount) * 100:0}%)";
                }
                break;
        }

        return scoreText;
    }
}
```

# 수정된 코드

```C#
public class RankingUserListSlot : UIElement
{
    [SerializeField] private MemberSlot m_memberSlot;

    [SerializeField] private TextMeshProUGUI m_score;
    [SerializeField] private Image m_rankImage;
    [SerializeField] private TextMeshProUGUI m_rankText;

    [SerializeField] private GameObject m_myRank;

    private RankingInfoDesc m_rankingInfoDesc = new RankingInfoDesc();

    public void SetRanking(RankingTypeEnum rankingType, PKS_RANKING_INFO pks)
    {
        SetRankingNumber(pks.rank);
        SetScoreByRankingType(rankingType, pks.currentValue);
        InitRankingInfoDesc(pks.desc);
        UpdateMemberSlot(pks);
        SetMyRank(pks);
    }

    private void SetRankingNumber(int rank)
    {
        if (rank <= 3)
            SetTopThree(rank);
        else
            SetUnderThree(rank);
    }

    private void SetScoreByRankingType(RankingTypeEnum rankingType, int score)
    {
        string scoreText = score.ToString();

        switch (rankingType)
        {
            case RankingTypeEnum.Level:
                scoreText = GetLevelRankingScoreText(score);
                break;

            case RankingTypeEnum.Combat:
                scoreText = UIUtil.GetCommaedText(score);               
                break;

            case RankingTypeEnum.RecordItem:
                scoreText = GetRecordItemRankingScoreText(score);
                break;

            case RankingTypeEnum.RecordRelationship:
                scoreText = GetRecordRelationshipRankingScoreText(score);
                break;

            case RankingTypeEnum.Adventure:
                scoreText = GetAdventureRankingScoreText(score);
                break;
        }

        m_score.text = scoreText;
    }
    
    private void InitRankingInfoDesc(string desc)
    {
        m_rankingInfoDesc.Init(desc);
    }
    
     private void UpdateMemberSlot(PKS_RANKING_INFO pks)
    {
        m_memberSlot.SetMember(pks.aid, pks.accountName, m_rankingInfoDesc.TitleName, m_rankingInfoDesc.GuildName, false,
            m_rankingInfoDesc.Level, m_rankingInfoDesc.ProfileSkinID, null, m_rankingInfoDesc.GenderType);
        var jobData = JobAMData.FromTable(m_rankingInfoDesc.JobID);
        m_memberSlot.SetHeadImage(jobData);
    }

    private void SetMyRank(PKS_RANKING_INFO pks)
    {
        bool myRank = pks.aid == ClientData.GetAccountGUID();
        m_myRank.SetActive(myRank);
    }

    private string GetLevelRankingScoreText(int score)
    {
        int level = 0;
        long maxExp = 0;
        var expTable = Manager.GetEXPTable(Strings.Character);
        EXPCalculate.GetEXP(expTable, score, 1, out level, out maxExp);

        double percent = (float)score / maxExp;
        string scoreText = $"Lv.{level} ({Mathf.Floor((float)percent * 10) / 10:0.0}%)";

        return scoreText;
    }

    private string GetRecordItemRankingScoreText(int score)
    {
        int maxCount = Manager.GetItemMasterTable().ConditionMaxCount;
        double percent = (float)score / maxCount * 100;
        string scoreText = $"{score}/{maxCount} ({Mathf.Floor((float)(percent * 10)) / 10:0.0}%)";

        return scoreText;
    }

    private string GetRecordRelationshipRankingScoreText(int score)
    {
        int maxCount = Manager.GetRecordRelationshipTable().ConditionMaxCount;
        double percent = (float)score / maxCount * 100;
        string scoreText = $"{score}/{maxCount} ({Mathf.Floor((float)(percent * 10)) / 10:0.0}%)";

        return scoreText;
    }

    private string GetAdventureRankingScoreText(int score)
    {
        int maxCount = Manager.GetQuestTable().AdventureMaxCount;
        double percent = (float)score / maxCount * 100;
        string scoreText = $"{score}/{maxCount} ({Mathf.Floor((float)(percent * 10)) / 10:0.0}%)";

        return scoreText;
    }

    private void SetTopThree(int rank)
    {
        m_rankImage.enabled = true;
        m_rankImage.sprite = UIUtil.GetIcon("Common00", $"Rank{rank}nd");

        m_rankText.text = "";
    }

    private void SetUnderThree(int rank)
    {
        m_rankImage.enabled = false;

        m_rankText.text = rank.ToString();
    }
}
```

불필요한 주석을 삭제하고 해당 코드의 핵심이 되는 SetRanking 메서드의 내용을 역할에 맞게 메서드화 하여 분해 하였다. 

내부의 메서드들을 추상화 레벨에 맞게 배치하고 switch 문이 사용되는 SetScoreByRankingType 메서드를 제외하면 메서드의 크기도 가능한한 짧게 작성하였다.

코드의 전체적인 길이는 늘어났지만 각 메서드가 어떤 역할을 하며 어떤 기능을 하는지 보다 파악하기 쉬워졌다. 

클린코드의 내용을 가능한한 따르며 작성하고자 하였으며 보다 좋은 코드가 됐다고 생각하지만 프로그래밍에 정답은 없다.

사람에 따라서는 전체 코드가 길어져 보기 불편하다고 평가할 수 있으며 그러한 평가가 부당하다고 생각하지 않는다.

특히 프로젝트가 대형화가 될 수록 여러 사람들과의 협업은 필수이며 서로간의 피드백을 통해 보다 좋은 코드가 만들어 질 수 있다고 믿는다.

# 논의 내용

- 위의 코드 리팩토링 예시에 대해 어떻게 생각하는지 다른 프로그래머의 의견을 듣고 싶다. 

- 대형 프로젝트의 코드를 작성하다 보면 서로 다른 파일에서 거의 동일한 기능을 하는 코드들이 존재하게 된다.
해당 부분을 코드 내부에서 메서드화 하여 분리할 수는 있겠지만, 결국 서로 비슷한, 거의 같은 내용의 메서드들이 서로 다른 코드에 존재하게 된다. 
이런식으로 겹치는 기능들을 ~_Util 등의 이름을 붙인 클래스에 작성해서 중복을 피할 수 있겠지만 한편으로는 과하게 파편화가 되는게 아닌가 고민하게 된다.
여러분들 이라면 이러한 상황에서 어떠한 선택을 할지 의견을 나누고 싶다. (Util 클래스의 실질적인 활용도? 작업 편의성을 위해 클래스 내부의 메서드화를 시킬지, 중복 코드를 피하기 위해 다른 클래스에서 해당 메서드를 구현할지에 대한 선택 등)