import requests
from bs4 import BeautifulSoup
import os
from urllib.parse import urljoin

# Function to download PDFs
def download_pdf(url, directory, html_url):
    # Extract filename from URL
    filename = os.path.join(directory, url.split('/')[-1])
    
    # Ensure URL is absolute
    if not url.startswith('http'):
        url = urljoin(html_url, url)
        
    # Download PDF
    with open(filename, 'wb') as f:
        response = requests.get(url)
        f.write(response.content)

# Function to extract PDF URLs from HTML
def extract_pdf_links(html_content, html_url):
    soup = BeautifulSoup(html_content, 'html.parser')
    pdf_links = []
    for link in soup.find_all('a'):
        href = link.get('href')
        if href and href.endswith('.pdf'):
            pdf_links.append(href)
    return pdf_links

# Main function
def main():
    # URL of the HTML page
    html_url = 'https://www.cubawiki.com.ar/index.php/Algoritmos_y_Estructuras_de_Datos_III'
    
    # Directory to save PDFs
    save_directory = 'pdfs'
    if not os.path.exists(save_directory):
        os.makedirs(save_directory)
    
    # Download PDFs
    response = requests.get(html_url)
    pdf_links = extract_pdf_links(response.content, html_url)
    for pdf_link in pdf_links:
        download_pdf(pdf_link, save_directory, html_url)

if __name__ == "__main__":
    main()
