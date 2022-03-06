#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Card
{
public:
    enum rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    friend ostream& operator<<(ostream& os, const Card& aCard)
    {
        const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
        const string SUITS[] = { "c", "d", "h", "s" };

        if (aCard.m_IsFaceUp)
            os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
        else
            os << "XX";

        return os;
    }

    Card(rank r = ACE, suit s = SPADES, bool ifu = true) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

    int GetValue() const
    {
        int value = 0;
        if (m_IsFaceUp)
        {
            value = m_Rank;
            if (value > 10)
                value = 10;
        }
        return value;
    }

    void Flip()
    {
        m_IsFaceUp = !(m_IsFaceUp);
    }

private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

class Hand
{
public:
    Hand()
    {
        m_Cards.reserve(7);
    }

    virtual ~Hand()
    {
        Clear();
    }

    void Add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }

    void Clear()
    {
        vector<Card*>::iterator iter = m_Cards.begin();
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            delete* iter;
            *iter = 0;
        }
        m_Cards.clear();
    }

    int GetTotal() const
    {
        if (m_Cards.empty())
            return 0;

        if (m_Cards[0]->GetValue() == 0)
            return 0;

        int total = 0;
        vector<Card*>::const_iterator iter;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
            total += (*iter)->GetValue();

        bool containsAce = false;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            if ((*iter)->GetValue() == Card::ACE)
                containsAce = true;
        }

        if (containsAce && total <= 11)
            total += 10;

        return total;
    }

protected:
    vector<Card*> m_Cards;
};

class GenericPlayer : public Hand
{
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
    {
        os << aGenericPlayer.m_Name << ":\t";

        vector<Card*>::const_iterator pCard;
        if (!aGenericPlayer.m_Cards.empty())
        {
            for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); ++pCard)
                os << *(*pCard) << "\t";

            if (aGenericPlayer.GetTotal() != 0)
                cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
        else
            os << "<empty>";

        return os;
    }

public:
    GenericPlayer(const string& name = "") : m_Name(name) {}

    virtual ~GenericPlayer() {}

    virtual bool IsHitting() const = 0;

    bool IsBusted() const
    {
        return (GetTotal() > 21);
    }

    void Bust() const
    {
        cout << m_Name << " busts.\n";
    }

protected:
    string m_Name;
};

class Player : public GenericPlayer
{
public:
    Player(const string& name = "") : GenericPlayer(name) {}

    virtual ~Player() {}

    virtual bool IsHitting() const
    {
        cout << m_Name << ", do you want a hit? (Y/N): ";
        char response;
        cin >> response;
        return (response == 'y' || response == 'Y');
    }

    void Win() const
    {
        cout << m_Name << " wins.\n";
    }

    void Lose() const
    {
        cout << m_Name << " loses.\n";
    }

    void Push() const
    {
        cout << m_Name << " pushes.\n";
    }
};

class House : public GenericPlayer
{
public:
    House(const string& name = "House") : GenericPlayer(name) {}

    virtual ~House() {}

    virtual bool IsHitting() const
    {
        return (GetTotal() <= 16);
    }

    void FlipFirstCard()
    {
        if (!(m_Cards.empty()))
            m_Cards[0]->Flip();
        else
            cout << "No card to flip!\n";
    }
};

class Deck : public Hand
{
public:
    Deck()
    {
        m_Cards.reserve(52);
        Populate();
    }

    virtual ~Deck() {}

    void Populate()
    {
        Clear();
        for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
        {
            for (int r = Card::ACE; r <= Card::KING; ++r)
                Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }

    void Shuffle()
    {
        random_shuffle(m_Cards.begin(), m_Cards.end());
    }

    void Deal(Hand& aHand)
    {
        if (!m_Cards.empty())
        {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else
            cout << "Out of cards. Unable to deal.";
    }

    void AdditionalCards(GenericPlayer& aGenericPlayer)
    {
        cout << endl;
        while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
        {
            Deal(aGenericPlayer);
            cout << aGenericPlayer << endl;

            if (aGenericPlayer.IsBusted())
                aGenericPlayer.Bust();
        }
    }
};

class Game
{
public:
    Game(const vector<string>& names)
    {
        vector<string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); ++pName)
        {
            m_Players.push_back(Player(*pName));
        }

        srand(static_cast<unsigned int>(time(0)));
        m_Deck.Populate();
        m_Deck.Shuffle();
    }

    ~Game() {}

    void Play()
    {
        vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i)
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                m_Deck.Deal(*pPlayer);

            m_Deck.Deal(m_House);
        }

        m_House.FlipFirstCard();

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            cout << *pPlayer << endl;

        cout << m_House << endl;

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            m_Deck.AdditionalCards(*pPlayer);

        m_House.FlipFirstCard();
        cout << endl << m_House;

        m_Deck.AdditionalCards(m_House);

        if (m_House.IsBusted())
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->IsBusted()))
                    pPlayer->Win();
            }
        }
        else
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->IsBusted()))
                {
                    if (pPlayer->GetTotal() > m_House.GetTotal())
                        pPlayer->Win();
                    else if (pPlayer->GetTotal() < m_House.GetTotal())
                        pPlayer->Lose();
                    else
                        pPlayer->Push();
                }
            }

        }

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            pPlayer->Clear();

        m_House.Clear();
    }

private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

void exercise_5();


class Date
{
private:
    int m_day;
    int m_month;
    int m_year;
public:
    Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}

    const int& getDay() const
    {
        return m_day;
    }

    const int& getMonth() const
    {
        return m_month;
    }

    const int& getYear() const
    {
        return m_year;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& d)
    {
        os << d.m_day << '.' << d.m_month << '.' << d.m_year;

        return os;
    }
};

template <class T>
class _ptr
{
private:
    T* m_ptr;
public:
    _ptr(T* ptr = nullptr) : m_ptr(ptr) {}
    ~_ptr() { delete m_ptr; }

    _ptr(_ptr& p)
    {
        m_ptr = p.m_ptr;
        p.m_ptr = nullptr;
    }

    _ptr& operator=(_ptr& p)
    {
        if (&p == this)
            return *this;

        delete m_ptr;
        m_ptr = p.m_ptr;
        p.m_ptr = nullptr;

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }

    bool isNull() const { return m_ptr == nullptr; }
};

const _ptr<Date>& compares_dates(const _ptr<Date>&, const _ptr<Date>&);

void exercise_1();
void exercise_2();


void exercise_1()
{
    _ptr<Date> today(new Date(10, 07, 2021));

    cout << "Day: " << today->getDay() << endl;
    cout << "Month: " << today->getMonth() << endl;
    cout << "Year: " << today->getYear() << endl;
    cout << "today: " << *today << endl;

    _ptr<Date> date;

    cout << "today is " << (today.isNull() ? "null\n" : "not null\n");
    cout << "date is " << (date.isNull() ? "null\n" : "not null\n");

    date = today;

    cout << "today is " << (today.isNull() ? "null\n" : "not null\n");
    cout << "date is " << (date.isNull() ? "null\n" : "not null\n");

    cout << "date: " << *date << endl;
}


const _ptr<Date>& compares_dates(const _ptr<Date>& a, const _ptr<Date>& b)
{
    if (a->getYear() > b->getYear())
        return a;
    else if (a->getYear() < b->getYear())
        return b;
    else
    {
        if (a->getMonth() > b->getMonth())
            return a;
        else if (a->getMonth() < b->getMonth())
            return b;
        else
        {
            if (a->getDay() > b->getDay())
                return a;
            else
                return b;
        }
    }
}

void swap_dates(_ptr<Date>& a, _ptr<Date>& b)
{
    _ptr<Date> temp(a);
    a = b;
    b = temp;
}

void exercise_2()
{
    _ptr<Date> date1(new Date(9, 07, 2022));
    _ptr<Date> date2(new Date(10, 07, 2022));
    _ptr<Date> date3(new Date(11, 07, 2022));

    std::cout << *compares_dates(date1, date2) << std::endl;
    swap_dates(date2, date3);
    std::cout << *compares_dates(date1, date2) << std::endl;
}


void exercise_5()
{
    cout << "\t\tWelcome to Blackjack!\n\n";

    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }

    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;

    
    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }
}

int main()
{
    exercise_1();
    exercise_2();
    exercise_5();

    return 0;
}