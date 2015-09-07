/*      _           _          _           _             _            _          _      _
       / /\        /\ \       /\ \        _\ \          /\ \         /\ \       /\ \   /\_\
      / /  \       \ \ \     /  \ \      /\__ \        /  \ \       /  \ \     /  \ \ / / /         _
     / / /\ \__    /\ \_\   / /\ \ \    / /_ \_\      / /\ \ \     / /\ \ \   / /\ \ \\ \ \__      /\_\
    / / /\ \___\  / /\/_/  / / /\ \_\  / / /\/_/     / / /\ \_\   / / /\ \_\ / / /\ \ \\ \___\    / / /
    \ \ \ \/___/ / / /    / / /_/ / / / / /         / /_/_ \/_/  / /_/_ \/_// / /  \ \_\\__  /   / / /
     \ \ \      / / /    / / /__\/ / / / /         / /____/\    / /____/\  / / /   / / // / /   / / /
 _    \ \ \    / / /    / / /_____/ / / / ____    / /\____\/   / /\____\/ / / /   / / // / /   / / /
/_/\__/ / /___/ / /__  / / /\ \ \  / /_/_/ ___/\ / / /______  / / /      / / /___/ / // / /___/ / /
\ \/___/ //\__\/_/___\/ / /  \ \ \/_______/\__\// / /_______\/ / /      / / /____\/ // / /____\/ /
 \_____\/ \/_________/\/_/    \_\/\_______\/    \/__________/\/_/       \/_________/ \/_________/
*/

#include "ActionInventory.hpp"

ActionInventory::ActionInventory()
{

}

ActionInventory::ActionInventory(ActionInventory const & model)
{
	*this = model;
}

ActionInventory::~ActionInventory()
{

}

std::string		ActionInventory::toString() const
{
	return "ActionInventory";
}

ActionInventory&	ActionInventory::operator=(ActionInventory const & copy)
{
	if (this != &copy)
		(void)copy;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, ActionInventory const & i)
{
	o << i.toString();
	return o;
}

int				ActionInventory::execute(Network & network)
{
	std::string	ret;

	ret = network.send(INVENTORY);
	if (ret == Network::MSG_FAILURE)
		return _failIndex;

	Client					*c = Action::client;
	Inventory				&i = c->getInventory();
	std::regex 				re("([\\w \\d]*)[,}]");
	std::sregex_iterator 	next(ret.begin(), ret.end(), re);
	std::sregex_iterator	end;
	std::string				tmp;

	i.clear();
	while (next != end)
	{
		std::smatch match = *next;
		std::smatch	sm;
		tmp = match.str();
		if (tmp[0] == ' ')
			tmp = match.str().substr(1);
		tmp.resize(tmp.size() - 1);
		std::regex_match(tmp, sm, std::regex("(\\w+)\\s+(\\d+)"));
		if (sm[2].str() == "")
			break;
		i.set(sm[1].str(), std::stol(sm[2].str()));
		++next;
	}
	return _successIndex;
}
