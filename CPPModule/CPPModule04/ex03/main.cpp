/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:18:23 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 12:18:24 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include <iomanip>

int main(void)
{
  std::cout << RED;
  std::cout << "=================create=================" << std::endl;
  std::cout << RESET;
  IMateriaSource* src = new MateriaSource();
  AMateria* tmp;
  ICharacter* me = new Character("me");
  ICharacter* bob = new Character("bob");

  std::cout << RED;
  std::cout << "=================learn Materia=================" << std::endl;
  std::cout << RESET;
  tmp = src->createMateria("ice");
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());

  std::cout << RED;
  std::cout << "=================create Materia=================" << std::endl;
  std::cout << RESET;
  AMateria* tmp0;
  AMateria* tmp1;
  AMateria* tmp2;
  tmp0 = src->createMateria("ice");
  me->equip(tmp0);
  tmp1 = src->createMateria("cure");
  me->equip(tmp1);
  tmp2 = src->createMateria("name");
  tmp2 = src->createMateria("ice");
  me->equip(tmp2);

  std::cout << RED;
  std::cout << "=================learn Materia 5 more=================" << std::endl;
  std::cout << RESET;
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());
  src->learnMateria(new Cure());

  std::cout << RED;
  std::cout << "=================character use Materia=================" << std::endl;
  std::cout << RESET;
  me->use(0, *bob);
  me->use(1, *bob);
  me->use(2, *bob);

  std::cout << RED;
  std::cout << "=================character equip 5 more Materia=================" << std::endl;
  std::cout << RESET;
  AMateria  *ice = new Ice();
  AMateria  *cure = new Cure();
  me->equip(cure);
  me->use(2, *bob);
  me->equip(cure);
  me->equip(ice);

  std::cout << RED;
  std::cout << "=================character unequip and use=================" << std::endl;
  std::cout << RESET;
  me->unequip(0);
  delete tmp0;
  me->use(1, *bob);
  me->use(2, *bob);

  std::cout << RED;
  std::cout << "=================delete=================" << std::endl;
  std::cout << RESET;
  delete bob;
  delete me;
  delete src;

  return 0;
}

