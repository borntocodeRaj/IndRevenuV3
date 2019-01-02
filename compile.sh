if [ $# != 5 ]
then
  echo 'prealable: positionner TWO_TASK sur la base cible: TWO_TASK=basecible'
  echo 'usage: make.sh userrev pwdrev userope pwdope baseop'
  echo 'userrev : utilisateur batch base revenu'
  echo 'pwdrev  : mot de passe de utilisateur userrev'
  echo 'userope : utilisateur batch base operationnelle Corail ou Thalys'
  echo 'pwdope  : mot de passe de utilisateur userope'
  echo 'baseop : nom de la base operationelle'
  exit 1
fi
rm *.o
rm *.lis
./rmbuiltcpp.sh
export PROPRIO_BASE=$1/$2
export IPROPRIO_BASE=$3/$4
export IBASE=$5
make -f MakeFile indrevenuV3
