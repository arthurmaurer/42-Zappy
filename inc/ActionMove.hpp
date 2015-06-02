#ifndef ACTIONMOVE_HEADER
#define ACTIONMOVE_HEADER

#include <string>
#include <iostream>
#include "IAction.hpp"
#include "eDirection.hpp"

class ActionMove : public IAction
{
public:
	ActionMove(enum eDirection);
	ActionMove(ActionMove const &);
	virtual ~ActionMove();
	std::string	toString() const;

	ActionMove&	operator=(ActionMove const &);

	virtual void	execute(Network &network);

private:
  	static std::map<enum eDirection, std::string>		_directionMap;
	enum eDirection		_dir;
};

std::ostream	&operator<<(std::ostream &o, ActionMove const &i);

#endif /*ACTIONMOVE_HEADER*/
