cp proper-requirements.txt blocknote-master/requirements.txt
cd blocknote-master
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
sed -i "s/'base'/'todoapp'/g" apps/todoapp/apps.py
python3 manage.py makemigrations
python3 manage.py migrate
python3 manage.py runserver