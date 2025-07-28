#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 big;

struct Pt {
    ll x;
    big y;
};

big todec(const string& s, int base) {
    big num = 0;
    for (char c : s) {
        int val;
        if (isdigit(c)) val = c - '0';
        else val = tolower(c) - 'a' + 10;
        num = num * base + val;
    }
    return num;
}

big li(vector<Pt>& points, int k) {
    big result = 0;
    for (int i = 0; i < k; ++i) {
        big xi = points[i].x;
        big yi = points[i].y;
        big num = 1, den = 1;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                num *= -points[j].x;
                den *= (xi - points[j].x);
            }
        }
        result += yi * (num / den);
    }
    return result;
}

void print(big x) {
    if (x == 0) {
        cout << "0\n";
        return;
    }
    string res;
    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }
    while (x) {
        res += char('0' + x % 10);
        x /= 10;
    }
    if (neg) res += '-';
    reverse(res.begin(), res.end());
    cout << res << '\n';
}

void f(const string& js) {
    vector<Pt> points;
    int n = 0, k = 0;

    regex pairReg("\"(\\d+)\"\\s*:\\s*\\{\\s*\"base\"\\s*:\\s*\"(\\d+)\",\\s*\"value\"\\s*:\\s*\"([a-zA-Z0-9]+)\"\\s*\\}");
    smatch match;

    regex keysReg("\"keys\"\\s*:\\s*\\{[^\\}]*\"n\"\\s*:\\s*(\\d+),\\s*\"k\"\\s*:\\s*(\\d+)");
    if (regex_search(js, match, keysReg)) {
        n = stoi(match[1]);
        k = stoi(match[2]);
    }

    auto begin = sregex_iterator(js.begin(), js.end(), pairReg);
    auto end = sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        int x = stoi((*it)[1]);
        int base = stoi((*it)[2]);
        string val = (*it)[3];
        big y = todec(val, base);
        points.push_back({x, y});
    }

    sort(points.begin(), points.end(), [](const Pt& a, const Pt& b) {
        return a.x < b.x;
    });

    points.resize(k);

    big secret = li(points, k);
    print(secret);
}

int main() {
    string a = R"({
        "keys": {
            "n": 4,
            "k": 3
        },
        "1": {
            "base": "10",
            "value": "4"
        },
        "2": {
            "base": "2",
            "value": "111"
        },
        "3": {
            "base": "10",
            "value": "12"
        },
        "6": {
            "base": "4",
            "value": "213"
        }
    })";

    string b = R"({
      "keys": {
        "n": 10,
        "k": 7
      },
      "1": {
        "base": "6",
        "value": "13444211440455345511"
      },
      "2": {
        "base": "15",
        "value": "aed7015a346d63"
      },
      "3": {
        "base": "15",
        "value": "6aeeb69631c227c"
      },
      "4": {
        "base": "16",
        "value": "e1b5e05623d881f"
      },
      "5": {
        "base": "8",
        "value": "316034514573652620673"
      },
      "6": {
        "base": "3",
        "value": "2122212201122002221120200210011020220200"
      },
      "7": {
        "base": "3",
        "value": "20120221122211000100210021102001201112121"
      },
      "8": {
        "base": "6",
        "value": "20220554335330240002224253"
      },
      "9": {
        "base": "12",
        "value": "45153788322a1255483"
      },
      "10": {
        "base": "7",
        "value": "1101613130313526312514143"
      }
    })";

    f(a);
    f(b);

    return 0;
}
