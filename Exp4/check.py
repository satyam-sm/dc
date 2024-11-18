from lxml import etree

# Load the XML and XSD files
xml_file = 'Exp4/cricket.xml'
xsd_file = 'Exp4/cricket.xsd'

# Load schema from file
with open(xsd_file, 'r') as schema_file:
    schema_doc = etree.parse(schema_file)
    schema = etree.XMLSchema(schema_doc)

# Load XML file
with open(xml_file, 'r') as xml_file:
    xml_doc = etree.parse(xml_file)

# Validate
try:
    schema.assertValid(xml_doc)
    print("Cricket XML is valid.")
except etree.DocumentInvalid as e:
    print("Cricket XML is invalid:", e)
