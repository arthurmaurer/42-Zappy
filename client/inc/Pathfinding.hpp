#ifndef PATHFINDING_HEADER
#define PATHFINDING_HEADER

#include <string>
#include <iostream>

class Client;

class Pathfinding
{
public:
	Pathfinding(Client &);
	Pathfinding(Pathfinding const &);
	virtual ~Pathfinding();
	std::string	toString() const;

	Pathfinding&	operator=(Pathfinding const &);

	size_t						getCaseX(int i);
	size_t						getCaseY(int i);
	std::pair<size_t, size_t>	getPairCase(int x, int y);
	void						pathfinding(std::pair<size_t, size_t>, std::pair<size_t, size_t>);

	int			getTotalCase(int k);
	int			getNbcircle(int n);
	int			getCirclePos(int n);
	void		getOffset(int circle, int pos, int XY[2]);
	void		Pos(int n, int XY[2]);

private:
	Client		&_client;

};

std::ostream	&operator<<(std::ostream &o, Pathfinding const &i);

#endif /*PATHFINDING_HEADER*/