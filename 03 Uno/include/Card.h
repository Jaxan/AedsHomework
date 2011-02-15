#ifndef CARD_H
#define CARD_H



class Card {
public:
	enum Kind {
		Yellow,
		Green,
		Red,
		Blue,
		Choice,
		ChoicePick4
	};

	enum Value {
		Nothing	= -1,
		Pick2	= 10,
		Turn	= 11,
		Skip	= 12
	};


	Card (Kind kind, int value = Nothing) : kind (kind), value (value) {}

	/**
	     * getter voor soort, geen setter want kaarten worden nooit veranderd
	     * @return het soort van deze kaart
	     */
	Kind getKind() {
		return kind;
	}

	/**
	 * getter voor waarde
	 * @return de waarde indien deze bestaat, anders -1
	 */
	int getValue() {
		return value;
	}

	/**
	     * gaat na of deze kaart op de gegeven kaart past
	     * @param c de kaart waar deze bovenop zou moeten
	     * @return of het past
	     * PAS OP: deze test is iets te simpel
	     */
	bool fitsOn (const Card & c) {
		return kind == c.kind || value == c.value;
	}

	/**
	 * maakt een nette string die deze kaart beschrijft
	 * @return de beschrijving van deze kaart
	 */
	friend std::ostream& operator<< (std::ostream& out, const Card& rh);

protected:
private:

	Kind kind;
	int value;
};

std::ostream& operator<< (std::ostream& out, const Card& rh) {
	switch (rh.kind) {
		case Card::Yellow:
			out << "Geel"; break;
		case Card::Green:
			out << "Groen"; break;
		case Card::Red:
			out << "Rood"; break;
		case Card::Blue:
			out << "Blauw"; break;
		case Card::Choice:
			out << "Keuze"; break;
		case Card::ChoicePick4:
			out << "KeuzePak4"; break;
		default:
			out << "Onbekend soort"; break;
	}
	switch (rh.kind) {
		case Card::Choice:
		case Card::ChoicePick4:
			break;
		default:
			switch (rh.value) {
				case Card::Pick2:
					out << " 2 pakken";
				case Card::Turn:
					out << " keer om";
				case Card::Skip:
					out << " beurt overslaan";
				default:
					out << " " << rh.value;
			}
	}

	return out;
}

#endif // CARD_H
