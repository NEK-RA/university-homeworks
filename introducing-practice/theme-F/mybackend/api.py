from pathlib import Path
from requests import get
from bs4 import BeautifulSoup

class API:

  @staticmethod
  def getSchedulePage():
    response = get("https://mirea.ru/schedule/", headers={"user-agent":"curl/7.80"})
    if(response.status_code == 200):
      return response.text
    else:
      raise ValueError(f"(HTTP code {response.headers['status']})")
  
  @staticmethod
  def getScheduleLinks():
    html = API.getSchedulePage()
    soup = BeautifulSoup(html, "html.parser")
    iitpart = soup.find("div",{"class": "schedule"})\
      .find(string="Институт информационных технологий")\
        .findParent("div")\
          .findParent("div")\
            .findAll("a")
    links = []
    for link in iitpart:
      xls = "xlsx" in link.attrs["href"].lower()
      exam = "ekz" in link.attrs["href"].lower()
      zach = "zach"  in link.attrs["href"].lower()
      if xls and not exam and not zach:
        links.append(link.attrs["href"])
    return links

  @staticmethod
  def getScheduleFilenames():
    links = API.getScheduleLinks()
    names = []
    for link in links:
      names.append(link.split("/")[-1])
    return names
  
  @staticmethod
  def downloadScheduleTo(folder):
    tfolder = Path(folder)
    if not tfolder.exists():
      tfolder.mkdir(parents=True)
    links = API.getScheduleLinks()
    results = []
    for link in links:
      filename = link.split("/")[-1]
      filepath = tfolder.joinpath(filename)
      
      download = get(link)
      if download.status_code == 200:
        with open(filepath.resolve().as_posix(), "wb") as dl:
          dl.write(download.content)
      else:
        raise ValueError("Invalid status code for the downloaded xlsx file")

    